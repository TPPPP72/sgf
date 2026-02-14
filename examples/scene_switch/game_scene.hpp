#pragma once

#include "sgf/type/color.hpp"
#include <iostream>
#include <sgf/base/renderer.hpp>
#include <sgf/scene/scene.hpp>
#include <sgf/timer.hpp>

class game_scene : public sgf::scene
{
public:
    game_scene(std::uint32_t id) : sgf::scene(id) {}

    void on_init() override
    {
        std::cout << "Game Scene Initialized.\n";
        m_log_timer.set_time(std::chrono::seconds(2));
        m_log_timer.set_callback([]()
                                 {
                                     std::cout << "[Game] 2 seconds passed in game world.\n";
                                 });
        m_log_timer.start();
    }

    void on_update(std::chrono::nanoseconds dt) override
    {
        m_log_timer.update(dt);
        double elapsed_sec = std::chrono::duration<double>(dt).count();
        m_player_pos += 100.0 * elapsed_sec * m_player_dir;
        if (m_player_pos >= 450 || m_player_pos <= 0)
            m_player_dir = -m_player_dir;
    }

    void on_render(sgf::base::renderer &rd) const override
    {
        double width  = 50.0;
        double height = 50.0;
        double y_pos  = 200.0;

        sgf::type::view_rect player_rect{
            m_player_pos,
            y_pos,
            width,
            height};

        sgf::type::view_rect background_rect{
            0,
            0,
            500,
            500};

        rd.render_rect(background_rect, sgf::type::color{209, 95, 238, 255});
        rd.render_rect(player_rect, sgf::type::color::green);
    }

private:
    sgf::timer m_log_timer;
    double m_player_pos{0.0};
    double m_player_dir{1};
};