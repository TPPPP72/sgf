#pragma once

#include <chrono>
#include <sgf/base/window/window_event.hpp>
#include <sgf/game_object/game_object.hpp>
#include <sgf/game_object/modules/camera_module.hpp>
#include <sgf/game_object/modules/keyboard_module.hpp>
#include <sgf/game_object/modules/mouse_module.hpp>
#include <sgf/game_object/modules/render_module.hpp>
#include <sgf/render_pipeline/render_pipeline.hpp>
#include <sgf/scene/scene.hpp>
#include <sgf/type/color.hpp>
#include <sgf/type/rect.hpp>

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

    void on_update(std::chrono::nanoseconds dt) override
    {
        auto keyboard = get_module<sgf::module::keyboard_module>();

        auto elapsed_sec = std::chrono::duration<double>(dt).count();

        if (keyboard->get_time(sgf::base::key_code::a) > std::chrono::nanoseconds(0))
            this->position().x -= 100 * elapsed_sec;
        if (keyboard->get_time(sgf::base::key_code::d) > std::chrono::nanoseconds(0))
            this->position().x += 100 * elapsed_sec;
        if (keyboard->get_time(sgf::base::key_code::w) > std::chrono::nanoseconds(0))
            this->position().y -= 100 * elapsed_sec;
        if (keyboard->get_time(sgf::base::key_code::s) > std::chrono::nanoseconds(0))
            this->position().y += 100 * elapsed_sec;

        auto mouse = get_module<sgf::module::mouse_module>();

        auto camera = get_module<sgf::module::camera_module>();

        if (mouse->get_time(sgf::base::mouse_button_code::left) > std::chrono::nanoseconds(0))
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

        render->pipeline()->submit(main->to_view_rect(rect), sgf::type::color::green, sgf::graphic_style::fill);
    }
};