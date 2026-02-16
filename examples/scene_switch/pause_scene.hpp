#pragma once

#include "sgf/base/renderer.hpp"
#include <iostream>
#include <sgf/scene/scene.hpp>
#include <sgf/timer.hpp>

class pause_scene : public sgf::scene
{
public:
    pause_scene(std::uint32_t id, sgf::scene *background) : sgf::scene(id), m_background(background)
    {
        if (m_background)
            m_background->should_update = false;
    }

    ~pause_scene() override
    {
        if (m_background)
            m_background->should_update = true;
    }

    void on_init() override
    {
        std::cout << "PauseScene: Logic suspended, rendering active.\n";
    }

    void on_update(std::chrono::nanoseconds dt) override
    {
    }

    void on_render(sgf::base::renderer &rd) const override
    {
        rd.render_rect({0, 0, 500, 500}, sgf::type::color{0, 0, 0, 150}, 1);
        rd.render_rect({150, 200, 200, 100}, sgf::type::color::white);
    }

private:
    sgf::scene *m_background;
};