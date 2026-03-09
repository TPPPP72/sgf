#include "ball.hpp"
#include "static_wall.hpp"
#include <memory>

class game_scene : public sgf::scene
{
public:
    game_scene(std::uint32_t id)
        : sgf::scene(id),
          m_camera({800, 600}, {800, 600}),
          m_physics_system(),
          m_context({{&m_camera}, &m_pipeline, &m_physics_system}),
          m_game_object_pool(m_context)
    {
    }

    void on_init() override
    {
        // --- 左斜坡 ---
        auto left        = std::make_unique<static_wall>(101);
        left->position() = {300, 400};
        left->size()     = {250, 20};
        left->rotation() = 0.785f;

        m_game_object_pool.create(std::move(left));

        // --- 右斜坡 ---
        auto right        = std::make_unique<static_wall>(102);
        right->position() = {500, 400};
        right->size()     = {250, 20};
        right->rotation() = -0.785f;

        m_game_object_pool.create(std::move(right));

        auto test_ball        = std::make_unique<ball>(1);
        test_ball->position() = {390.0f, 100.0f};
        m_game_object_pool.create(std::move(test_ball));
    }

    void on_input(const sgf::input_event &e) override
    {
        m_game_object_pool.input(e);
    }

    void on_update(const sgf::frame_context &ctx) override
    {
        m_physics_system.update(ctx.dt);

        m_game_object_pool.update(ctx);
    }

    void on_render(sgf::base::renderer &rd) override
    {
        m_game_object_pool.render();
        m_pipeline.execute(rd, nullptr);
    }

private:
    sgf::render::pipeline m_pipeline;
    sgf::camera m_camera;
    sgf::physics_system m_physics_system;

    sgf::scene_context m_context;
    sgf::game_object_pool m_game_object_pool;
};