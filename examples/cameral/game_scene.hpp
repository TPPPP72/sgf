#pragma once

#include <iostream>
#include <sgf/base/renderer.hpp>
#include <sgf/camera/camera.hpp>
#include <sgf/context/frame_context.hpp>
#include <sgf/event/input_event.hpp>
#include <sgf/scene/scene.hpp>
#include <sgf/timer/timer.hpp>
#include <sgf/type/color.hpp>

class game_scene : public sgf::scene
{
public:
    game_scene(std::uint32_t id)
        : sgf::scene(id),
          m_camera({800, 600}, {2000, 600}) {}

    void on_init() override
    {
        std::cout << "Camera Test Scene Initialized.\n";
        std::cout << "World size: 2000x600, View size: 800x600\n";
    }

    void on_input(const sgf::input_event &e) override
    {
    }

    void on_update(const sgf::frame_context &ctx) override
    {
        double elapsed_sec = std::chrono::duration<double>(ctx.dt).count();

        m_player_world_pos.x += 300.0 * elapsed_sec * m_player_dir;
        m_player_world_pos.y = 300.0;

        if (m_player_world_pos.x >= 1950 || m_player_world_pos.x <= 0)
            m_player_dir = -m_player_dir;

        m_camera.set_position(m_player_world_pos);
    }

    void on_render(sgf::base::renderer &rd) override
    {
        for (int i = 0; i <= 2000; i += 100)
        {
            sgf::type::world_rect line_rect{static_cast<double>(i), 0.0, 2.0, 600.0};
            rd.render_rect(m_camera.to_view_rect(line_rect),
                           sgf::type::color{100, 100, 100, 255},
                           1);
        }

        sgf::type::world_rect player_world_shape{
            m_player_world_pos.x,
            m_player_world_pos.y,
            50.0, 50.0};

        auto player_view_shape = m_camera.to_view_rect(player_world_shape);

        rd.render_rect(player_view_shape, sgf::type::color::green, 1);

        sgf::type::view_rect bar_bg{10, 10, 200, 20};
        rd.render_rect(bar_bg, {50, 50, 50, 255}, 1);

        double progress = m_player_world_pos.x / 2000.0;

        double indicator_x = bar_bg.x + (progress * (bar_bg.w - 10));

        sgf::type::view_rect indicator{
            static_cast<float>(indicator_x),
            bar_bg.y + 2,
            10.0,
            bar_bg.h - 4};

        rd.render_rect(indicator, {255, 255, 0, 255}, 1);
    }

private:
    sgf::camera m_camera;
    sgf::type::world_position m_player_world_pos{0.0, 300.0};
    double m_player_dir{1.0};
};