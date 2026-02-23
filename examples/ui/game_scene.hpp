#pragma once

#include "button.hpp"
#include <iostream>
#include <sgf/base/window/window_event.hpp>
#include <sgf/context/frame_context.hpp>
#include <sgf/event/input_event.hpp>
#include <sgf/render_pipeline/render_pipeline.hpp>
#include <sgf/scene/scene.hpp>
#include <sgf/ui/ui_manager.hpp>

class game_scene : public sgf::scene
{
public:
    game_scene(std::uint32_t id) : sgf::scene(id) {}

    void on_init() override
    {
        auto btn1 = std::make_shared<button>();
        btn1->set_pos(50, 50).set_size(80, 20);
        btn1->on_click = []()
        {
            std::cout << "clicked btn1\n";
        };

        auto btn2 = std::make_shared<button>();
        btn2->set_pos(55, 55).set_size(80, 20);
        btn2->on_click = []()
        {
            std::cout << "clicked btn2\n";
        };

        m_ui_manager.add_view(btn1);
        m_ui_manager.add_view(btn2);
    }

    void on_input(const sgf::input_event &e) override
    {
        m_ui_manager.dispatch(e);
    }

    void on_update(const sgf::frame_context &ctx) override
    {
        m_ui_manager.update(ctx);
    }

    void on_render(sgf::base::renderer &rd) override
    {
        m_ui_manager.render(m_pipeline);
        m_pipeline.execute(rd);
    }

private:
    sgf::render_pipeline m_pipeline;
    sgf::ui_manager m_ui_manager;
};