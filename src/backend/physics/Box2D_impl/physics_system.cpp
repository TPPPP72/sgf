#include <box2d/box2d.h>
#include <sgf/game_object/game_object.hpp>
#include <sgf/logger/logger.hpp>
#include <sgf/physics/physics_system.hpp>
#include <unordered_map>

struct entity_state
{
    sgf::game_object *owner;
    b2BodyId body_id = b2_nullBodyId;
    sgf::type::world_position last_pos;
};

struct sgf::physics_system::impl
{
    b2WorldId world_id = b2_nullWorldId;
    std::unordered_map<uint32_t, entity_state> entities;
};

sgf::physics_system::physics_system() : p_impl(std::make_unique<impl>())
{
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity    = {0.0f, 9.8f};

    p_impl->world_id = b2CreateWorld(&worldDef);
}

sgf::physics_system::~physics_system()
{
    if (B2_IS_NON_NULL(p_impl->world_id))
        b2DestroyWorld(p_impl->world_id);
}

void sgf::physics_system::register_entity(sgf::game_object &owner, const sgf::physics_config &config)
{
    auto &pos = owner.position();

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type      = static_cast<b2BodyType>(config.type);
    bodyDef.position  = {static_cast<float>(pos.x / PPM), static_cast<float>(pos.y / PPM)};
    bodyDef.rotation  = b2MakeRot(owner.rotation());
    bodyDef.userData  = reinterpret_cast<void *>(static_cast<uintptr_t>(owner.id()));

    b2BodyId bId = b2CreateBody(p_impl->world_id, &bodyDef);

    for (auto &col : config.colliders)
    {
        if (!col.is_circle && (col.w <= 0 || col.h <= 0))
            SGF_ERROR("Creating a box collider with zero size for GO ID: %u", owner.id());

        b2ShapeDef shapeDef = b2DefaultShapeDef();

        shapeDef.material.friction    = col.friction;
        shapeDef.material.restitution = col.restitution;

        shapeDef.density  = col.density;
        shapeDef.isSensor = col.is_sensor;

        shapeDef.enableContactEvents = true;

        if (col.is_circle)
        {
            b2Circle circle = {{0.0f, 0.0f}, col.radius / PPM};
            b2CreateCircleShape(bId, &shapeDef, &circle);
        }
        else
        {
            b2Polygon box = b2MakeBox((col.w * 0.5f) / PPM, (col.h * 0.5f) / PPM);
            b2CreatePolygonShape(bId, &shapeDef, &box);
        }
    }

    p_impl->entities[owner.id()] = {&owner, bId, pos};
}

void sgf::physics_system::apply_linear_impulse(uint32_t id, const sgf::type::vec2d &impulse)
{
    auto it = p_impl->entities.find(id);
    if (it != p_impl->entities.end())
        b2Body_ApplyLinearImpulse(it->second.body_id,
                                  {static_cast<float>(impulse.x), static_cast<float>(impulse.y)},
                                  b2Body_GetWorldCenterOfMass(it->second.body_id),
                                  true);
}

void sgf::physics_system::set_linear_velocity(uint32_t id, const sgf::type::vec2d &velocity)
{
    auto it = p_impl->entities.find(id);
    if (it != p_impl->entities.end() && B2_IS_NON_NULL(it->second.body_id))
    {
        b2Vec2 v = {
            static_cast<float>(velocity.x),
            static_cast<float>(velocity.y)};

        b2Body_SetLinearVelocity(it->second.body_id, v);
    }
}

void sgf::physics_system::update(std::chrono::nanoseconds dt)
{
    float time_step = std::chrono::duration<float>(dt).count();

    if (time_step > 0.0f)
        b2World_Step(p_impl->world_id, time_step, 4);

    for (auto &[id, state] : p_impl->entities)
    {
        if (B2_IS_NULL(state.body_id))
            continue;

        auto &tf = state.owner->transform();

        if (std::abs(tf.pos.x - state.last_pos.x) > 0.001f ||
            std::abs(tf.pos.y - state.last_pos.y) > 0.001f)
            SGF_ERROR("Physics Desync! GO(ID:%u) moved manually. Use sync_to_physics().", id);

        b2Vec2 p = b2Body_GetPosition(state.body_id);
        b2Rot r  = b2Body_GetRotation(state.body_id);

        tf.pos.x    = p.x * PPM;
        tf.pos.y    = p.y * PPM;
        tf.rotation = b2Rot_GetAngle(r);

        state.last_pos = tf.pos;
    }
}

void sgf::physics_system::sync_to_physics(uint32_t id)
{
    auto it = p_impl->entities.find(id);
    if (it != p_impl->entities.end() && B2_IS_NON_NULL(it->second.body_id))
    {
        auto &tf = it->second.owner->transform();

        b2Body_SetTransform(it->second.body_id,
                            {static_cast<float>(tf.pos.x / PPM), static_cast<float>(tf.pos.y / PPM)},
                            b2MakeRot(tf.rotation));

        it->second.last_pos = tf.pos;
    }
}

void sgf::physics_system::unregister_entity(uint32_t id)
{
    auto it = p_impl->entities.find(id);
    if (it != p_impl->entities.end())
    {
        if (B2_IS_NON_NULL(it->second.body_id))
            b2DestroyBody(it->second.body_id);
        p_impl->entities.erase(it);
    }
}