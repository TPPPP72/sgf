#include "../include/sgf/input_system.hpp"
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
    bool now  = win->current_event().keys.count(key) ? win->current_event().keys.at(key) : false;
    bool prev = previous.keys.count(key) ? previous.keys.at(key) : false;
    return now && !prev;
}

bool input_system::is_key_down(base::key_code key) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    return win->current_event().keys.count(key) ? win->current_event().keys.at(key) : false;
}

bool input_system::is_key_released(base::key_code key) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    if (!has_call_update && win->poll_event_count() > 1)
        throw std::runtime_error("Please call update after calling released");
    bool now  = win->current_event().keys.count(key) ? win->current_event().keys.at(key) : false;
    bool prev = previous.keys.count(key) ? previous.keys.at(key) : false;
    return !now && prev;
}

bool input_system::is_button_pressed(base::mouse_button_code button) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    if (!has_call_update && win->poll_event_count() > 1)
        throw std::runtime_error("Please call update after calling pressed");
    bool now  = win->current_event().buttons.count(button) ? win->current_event().buttons.at(button) : false;
    bool prev = previous.buttons.count(button) ? previous.buttons.at(button) : false;
    return now && !prev;
}

bool input_system::is_button_down(base::mouse_button_code button) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    return win->current_event().buttons.count(button) ? win->current_event().buttons.at(button) : false;
}

bool input_system::is_button_released(base::mouse_button_code button) const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    if (!has_call_update && win->poll_event_count() > 1)
        throw std::runtime_error("Please call update after calling released");
    bool now  = win->current_event().buttons.count(button) ? win->current_event().buttons.at(button) : false;
    bool prev = previous.buttons.count(button) ? previous.buttons.at(button) : false;
    return !now && prev;
}

base::mouse_position input_system::get_mouse_position() const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");
    return win->current_event().pos;
}

base::mouse_position input_system::get_logic_mouse_position() const
{
    if (win == nullptr)
        throw std::runtime_error("Can not use input_system before bind");

    auto [current_w, current_h] = win->current_size();
    auto [init_w, init_h]       = win->init_size();
    auto x                      = win->current_event().pos.x * (static_cast<double>(init_w) / current_w);
    auto y                      = win->current_event().pos.y * (static_cast<double>(init_h) / current_h);
    return {x, y};
}