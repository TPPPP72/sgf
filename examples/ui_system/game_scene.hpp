#pragma once

#include "button.hpp"

class game_scene : public sgf::scene
{
public:
    game_scene(std::uint32_t id) : sgf::scene(id) {}

    void on_init() override
    {
        float x             = 0;
        float y             = 0;
        std::uint32_t count = 1;
        while (x <= 800 && y <= 600)
        {
            auto btn = std::make_shared<button>();
            btn->set_pos(x, y).set_size(80, 20);
            btn->on_click = [&x, &y, count]()
            {
                std::cout << "clicked btn" << std::to_string(count) << '\n';
            };
            x += 40;
            y += 10;
            ++count;
            m_ui_manager.add_view(btn);
        }
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
        m_pipeline.execute(rd, nullptr);
    }

private:
    sgf::render::pipeline m_pipeline;
    sgf::ui_manager m_ui_manager;
};