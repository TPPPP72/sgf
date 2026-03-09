#pragma once

#include "square.hpp"
#include <memory>

class game_scene : public sgf::scene
{
public:
    game_scene(std::uint32_t id)
        : sgf::scene(id), m_camera({300, 300}, {300, 300}),
          m_context({{&m_camera}, &m_pipeline}),
          m_game_object_pool(m_context) {}

    void on_init() override
    {
        m_game_object_pool.create(std::make_unique<square>(1));
    }

    void on_input(const sgf::input_event &e) override
    {
        m_game_object_pool.input(e);
    }

    void on_update(const sgf::frame_context &ctx) override
    {
        m_game_object_pool.update(ctx);
    }

    void on_render(sgf::base::renderer &rd) override
    {
        m_pipeline.submit_rect({0, 0, 300, 300}, sgf::type::color::white, sgf::render::style::fill, {0.0f, 0.0f}, 0.0f, sgf::render::layer::background);
        m_game_object_pool.render();
        m_pipeline.execute(rd, nullptr);
    }

private:
    sgf::render::pipeline m_pipeline;
    sgf::camera m_camera;

    sgf::scene_context m_context;
    sgf::game_object_pool m_game_object_pool;
};