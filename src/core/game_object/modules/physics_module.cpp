#include <sgf/game_object/game_object.hpp>
#include <sgf/game_object/modules/physics_module.hpp>

sgf::module::physics_module::physics_module(game_object &owner, scene_context &context, const physics_config &config)
    : base_service_module(owner, context)
{
    this->context().physics->register_entity(owner, config);
}

sgf::module::physics_module::~physics_module()
{
    this->context().physics->unregister_entity(owner().id());
}

void sgf::module::physics_module::apply_linear_impulse(const type::vec2d &impulse)
{
    this->context().physics->apply_linear_impulse(owner().id(), impulse);
}

void sgf::module::physics_module::set_linear_velocity(const type::vec2d &velocity)
{
    this->context().physics->set_linear_velocity(owner().id(), velocity);
}

void sgf::module::physics_module::sync_to_physics()
{
    this->context().physics->sync_to_physics(owner().id());
}