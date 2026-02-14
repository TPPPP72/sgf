#pragma once

#include <iostream>
#include <sgf/base/renderer.hpp>
#include <sgf/scene/scene.hpp>
#include <sgf/timer.hpp>

class game_scene : public sgf::scene
{
public:
    void init() override
    {
        std::cout << "Game Scene Initialized.\n";
        m_log_timer.set_time(std::chrono::seconds(2));
        m_log_timer.set_callback([]()
                                 {
                                     std::cout << "[Game] 2 seconds passed in game world.\n";
                                 });
        m_log_timer.start();
        id = "game";
    }

    void update(std::chrono::nanoseconds dt) override
    {
        m_log_timer.update(dt);
        double elapsed_sec = std::chrono::duration<double>(dt).count();
        m_player_pos += 100.0 * elapsed_sec;
    }

    void render(sgf::base::renderer &rd) override
    {
        float width  = 50.0f;
        float height = 50.0f;
        float y_pos  = 200.0f;

        sgf::type::view_rect player_rect{
            static_cast<float>(m_player_pos),
            y_pos,
            width,
            height};

        rd.render_rect(player_rect, sgf::type::color::green);
    }

private:
    sgf::timer m_log_timer;
    double m_player_pos{0.0};
};