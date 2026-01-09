#ifndef SGF_BASE_WINDOW_EVENT_HPP
#define SGF_BASE_WINDOW_EVENT_HPP

#include "../../type/position.hpp"
#include <array>
#include <cstdint>

namespace sgf::base
{

enum class event_type : std::uint8_t
{
    key_down,
    key_up,
    mouse_button_down,
    mouse_button_up,
    mouse_motion
};

enum class key_code : std::uint8_t
{
    unknown,
    a = 4,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    digit1,
    digit2,
    digit3,
    digit4,
    digit5,
    digit6,
    digit7,
    digit8,
    digit9,
    digit0,
    backspace = 42,
    tab,
    space,
    capslock = 57,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    right = 79,
    left,
    down,
    up,
    kp_digit1 = 89,
    kp_digit2,
    kp_digit3,
    kp_digit4,
    kp_digit5,
    kp_digit6,
    kp_digit7,
    kp_digit8,
    kp_digit9,
    kp_digit0,
    lctrl = 224,
    lshift,
    lalt,
    rctrl = 228,
    rshift,
    ralt
};

enum class mouse_button_code : std::uint8_t
{
    left = 1,
    middle,
    right
};

struct window_event
{
    std::array<bool, 5> events{false};
    type::window_position pos;
    std::array<bool, 231> keys{false};
    std::array<bool, 4> buttons{false};
};

}; // namespace sgf::base

#endif