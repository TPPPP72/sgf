#include <sgf/sgf.hpp>
#include "static_wall.hpp"
#include "sensor.hpp"
#include "rain.hpp"

class game_scene : public sgf::scene
{
public:
    game_scene(std::uint32_t id)
        : sgf::scene(id),
          m_camera({800, 600}, {800, 600}),
          m_physics_system(),
          m_context({{&m_camera}, &m_pipeline, &m_physics_system, &m_event_bus}),
          m_game_object_pool(m_context)
    {
    }

    void on_init() override
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        setup_environment();

        for (int i = 0; i < 500; ++i)
        {
            spawn_rain_drop(i);
        }
    }

    void on_input(const sgf::input_event &e) override
    {
        m_game_object_pool.input(e);
    }

    void on_update(const sgf::frame_context &ctx) override
    {
        m_physics_system.update(ctx.dt, &m_event_bus);
        m_event_bus.dispatch_all();
        m_game_object_pool.update(ctx);
    }

    void on_render(sgf::base::renderer &rd) override
    {
        m_game_object_pool.render();
        m_pipeline.execute(rd, nullptr);
    }

private:
    void setup_environment()
    {
        auto left        = std::make_unique<static_wall>(101);
        left->position() = {275, 400};
        left->size()     = {250, 20};
        left->rotation() = 0.785f;
        m_game_object_pool.create(std::move(left));

        auto right        = std::make_unique<static_wall>(102);
        right->position() = {525, 400};
        right->size()     = {250, 20};
        right->rotation() = -0.785f;
        m_game_object_pool.create(std::move(right));

        auto recycler        = std::make_unique<sensor>(103);
        recycler->position() = {400, 550};
        recycler->size()     = {800, 10};
        m_game_object_pool.create(std::move(recycler));
    }

    void spawn_rain_drop(int index)
    {
        auto drop = std::make_unique<rain>(index + 1000);

        float x = 250.0f + static_cast<float>(std::rand() % 300);
        float y = -static_cast<float>(std::rand() % 1000);

        drop->position() = {x, y};
        m_game_object_pool.create(std::move(drop));
    }

    sgf::render_pipeline m_pipeline;
    sgf::camera m_camera;
    sgf::physics_system m_physics_system;
    sgf::event_bus m_event_bus;

    sgf::scene_context m_context;
    sgf::game_object_pool m_game_object_pool;
};