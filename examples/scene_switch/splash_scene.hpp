#pragma once

#include <algorithm>
#include <chrono>
#include <sgf/base/renderer.hpp>
#include <sgf/context/frame_context.hpp>
#include <sgf/event/input_event.hpp>
#include <sgf/scene/scene.hpp>
#include <sgf/timer/timer.hpp>

using namespace std::chrono_literals;

class splash_scene : public sgf::scene
{
public:
    splash_scene(std::uint32_t id, std::function<void()> on_finish) : sgf::scene(id), m_on_finish(on_finish) {}

    void on_init() override
    {
        m_display_time = 0ns;
    }

    void on_input(const sgf::input_event &e) override
    {
    }

    void on_update(const sgf::frame_context &ctx) override
    {
        m_display_time += ctx.dt;

        if (m_display_time >= 3s)
            m_on_finish();
    }

    void on_render(sgf::base::renderer &rd) override
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