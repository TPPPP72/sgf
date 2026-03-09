#pragma once

#include <chrono>
#include <sgf/sgf.hpp>

class square : public sgf::game_object
{
public:
    using sgf::game_object::game_object;
    ~square() = default;

    void on_init(sgf::scene_context &ctx) override
    {
        this->position().x = 100;
        this->position().y = 100;
        this->size().w     = 100;
        this->size().h     = 100;
        add_module<sgf::module::keyboard_module>();
        add_module<sgf::module::mouse_module>();
        add_module<sgf::module::render_module>(ctx);
        add_module<sgf::module::camera_module>(ctx);
    }

    void on_update(const sgf::frame_context &ctx) override
    {
        auto keyboard = get_module<sgf::module::keyboard_module>();

        auto elapsed_sec = std::chrono::duration<double>(ctx.dt).count();

        if (keyboard->is_down(sgf::base::key_code::a))
            this->position().x -= 100 * elapsed_sec;
        if (keyboard->is_down(sgf::base::key_code::d))
            this->position().x += 100 * elapsed_sec;
        if (keyboard->is_down(sgf::base::key_code::w))
            this->position().y -= 100 * elapsed_sec;
        if (keyboard->is_down(sgf::base::key_code::s))
            this->position().y += 100 * elapsed_sec;

        auto mouse = get_module<sgf::module::mouse_module>();

        auto camera = get_module<sgf::module::camera_module>();

        if (mouse->is_down(sgf::base::mouse_button_code::left))
            this->position() = camera->get_main()->to_world_pos(mouse->position());
    }

    void on_render() override
    {
        auto render = get_module<sgf::module::render_module>();

        if (!render)
            return;

        auto [x, y] = this->position();
        auto [w, h] = this->size();

        sgf::type::world_rect rect = {
            x,
            y,
            static_cast<double>(w),
            static_cast<double>(h),
        };

        auto camera = get_module<sgf::module::camera_module>();
        auto main   = camera->get_main();

        render->pipeline()->submit_rect(main->to_view_rect(rect), sgf::type::color::green, sgf::render::style::fill, {0.5f, 0.5f}, rotation(), sgf::render::layer::entity);
    }
};