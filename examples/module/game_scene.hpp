#pragma once

#include "square.hpp"
#include <memory>
#include <sgf/base/renderer.hpp>
#include <sgf/camera/camera.hpp>
#include <sgf/context/frame_context.hpp>
#include <sgf/context/scene_context.hpp>
#include <sgf/event/input_event.hpp>
#include <sgf/game_object/game_object_pool.hpp>
#include <sgf/render_pipeline/render_pipeline.hpp>
#include <sgf/scene/scene.hpp>
#include <sgf/type/color.hpp>

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
        m_pipeline.submit_rect({0, 0, 300, 300}, sgf::type::color::white, sgf::graphic_style::fill, {0.0f, 0.0f}, 0.0f, sgf::render_layer::background);
        m_game_object_pool.render();
        m_pipeline.execute(rd, nullptr);
    }

private:
    sgf::render_pipeline m_pipeline;
    sgf::camera m_camera;

    sgf::scene_context m_context;
    sgf::game_object_pool m_game_object_pool;
};