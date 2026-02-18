#include "sgf/base/viewport.hpp"
#include "sgf/type/position.hpp"
#include <sgf/input/input_system.hpp>
#include <stdexcept>

using namespace sgf;

input_system &input_system::instance() noexcept
{
    static input_system instance;
    return instance;
}

void input_system::bind_window(base::window *w) noexcept
{
    win = w;
}

void input_system::bind_viewport(base::viewport *v) noexcept
{
    vp = v;
}

void input_system::update()
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind window");
    previous = win->current_event();
}

bool input_system::is_key_pressed(base::key_code key) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind window");
    bool now  = win->current_event().keys[static_cast<std::size_t>(key)];
    bool prev = previous.keys[static_cast<std::size_t>(key)];
    return now && !prev;
}

bool input_system::is_key_down(base::key_code key) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind window");
    return win->current_event().keys[static_cast<std::size_t>(key)];
}

bool input_system::is_key_released(base::key_code key) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind window");
    bool now  = win->current_event().keys[static_cast<std::size_t>(key)];
    bool prev = previous.keys[static_cast<std::size_t>(key)];
    return !now && prev;
}

bool input_system::is_button_pressed(base::mouse_button_code button) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind window");
    bool now  = win->current_event().buttons[static_cast<std::size_t>(button)];
    bool prev = previous.buttons[static_cast<std::size_t>(button)];
    return now && !prev;
}

bool input_system::is_button_down(base::mouse_button_code button) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind window");
    return win->current_event().buttons[static_cast<std::size_t>(button)];
}

bool input_system::is_button_released(base::mouse_button_code button) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind window");
    bool now  = win->current_event().buttons[static_cast<std::size_t>(button)];
    bool prev = previous.buttons[static_cast<std::size_t>(button)];
    return !now && prev;
}

type::window_position input_system::get_mouse_window_position() const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind window");
    return win->current_event().pos;
}

type::view_position input_system::get_mouse_view_position() const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind window");
    if (vp == nullptr)
        throw std::runtime_error("Can not use get_mouse_view_position before bind viewport");
    return vp->to_view_position(win->current_event().pos);
}