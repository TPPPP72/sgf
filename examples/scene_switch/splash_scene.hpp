#pragma once

#include <algorithm>
#include <chrono>
#include <sgf/scene/scene.hpp>
#include <sgf/timer.hpp>

using namespace std::chrono_literals;

class splash_scene : public sgf::scene
{
public:
    splash_scene(std::function<void()> on_finish) : m_on_finish(on_finish) {}

    void init() override
    {
        m_display_time = 0ns;
        id             = "splash";
    }

    void update(std::chrono::nanoseconds dt) override
    {
        m_display_time += dt;

        if (m_display_time >= 3s)
            m_on_finish();
    }

    void render(sgf::base::renderer &rd) override
    {
        rd.render_rect({0, 0, 500, 500}, sgf::type::color::black);

        double progress = std::min(1.0, std::chrono::duration<double>(m_display_time).count() / 3.0);

        float bar_width = 300.0f;
        float x         = 100.0f;

        rd.render_rect({x, 400, bar_width, 10}, sgf::type::color{40, 40, 40, 255});
        rd.render_rect({x, 400, static_cast<float>(bar_width * progress), 10}, sgf::type::color::white);
    }

private:
    std::chrono::nanoseconds m_display_time{0};
    std::function<void()> m_on_finish;
};