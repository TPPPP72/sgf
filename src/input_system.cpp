#include <sgf/input_system.hpp>
#include <stdexcept>

using namespace sgf;

input_system &input_system::instance() noexcept
{
    static input_system instance;
    return instance;
}

void input_system::bind(base::window *w) noexcept
{
    win = w;
}

void input_system::update()
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    previous        = win->current_event();
    has_call_update = true;
}

bool input_system::is_key_pressed(base::key_code key) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    if (!has_call_update && win->poll_event_count() > 1)
        throw std::runtime_error("Please call update after calling pressed");
    bool now  = win->current_event().keys[static_cast<std::size_t>(key)];
    bool prev = previous.keys[static_cast<std::size_t>(key)];
    return now && !prev;
}

bool input_system::is_key_down(base::key_code key) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    return win->current_event().keys[static_cast<std::size_t>(key)];
}

bool input_system::is_key_released(base::key_code key) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    if (!has_call_update && win->poll_event_count() > 1)
        throw std::runtime_error("Please call update after calling released");
    bool now  = win->current_event().keys[static_cast<std::size_t>(key)];
    bool prev = previous.keys[static_cast<std::size_t>(key)];
    return !now && prev;
}

bool input_system::is_button_pressed(base::mouse_button_code button) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    if (!has_call_update && win->poll_event_count() > 1)
        throw std::runtime_error("Please call update after calling pressed");
    bool now  = win->current_event().buttons[static_cast<std::size_t>(button)];
    bool prev = previous.buttons[static_cast<std::size_t>(button)];
    return now && !prev;
}

bool input_system::is_button_down(base::mouse_button_code button) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    return win->current_event().buttons[static_cast<std::size_t>(button)];
}

bool input_system::is_button_released(base::mouse_button_code button) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    if (!has_call_update && win->poll_event_count() > 1)
        throw std::runtime_error("Please call update after calling released");
    bool now  = win->current_event().buttons[static_cast<std::size_t>(button)];
    bool prev = previous.buttons[static_cast<std::size_t>(button)];
    return !now && prev;
}

type::window_position input_system::get_mouse_position() const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    return win->current_event().pos;
}