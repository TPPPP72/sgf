#pragma once

#include <iostream>
#include <sgf/scene/scene.hpp>
#include <sgf/timer.hpp>

class pause_scene : public sgf::scene
{
public:
    pause_scene(sgf::scene *background) : m_background(background)
    {
        if (m_background)
            m_background->should_update = false;
        id = "pause";
    }

    ~pause_scene() override
    {
        if (m_background)
            m_background->should_update = true;
    }

    void init() override
    {
        std::cout << "PauseScene: Logic suspended, rendering active.\n";
    }

    void update(std::chrono::nanoseconds dt) override
    {
    }

    void render(sgf::base::renderer &rd) override
    {
        rd.render_rect({0, 0, 500, 500}, sgf::type::color{0, 0, 0, 150});
        rd.render_rect({150, 200, 200, 100}, sgf::type::color::white);
    }

private:
    sgf::scene *m_background;
};