#ifndef SGF_INPUT_EVENT_HPP
#define SGF_INPUT_EVENT_HPP

#include <sgf/base/window/window_event.hpp>

namespace sgf
{

struct input_event
{
    base::event_type type{base::event_type::none};
    base::key_code key{base::key_code::none};
    base::mouse_button_code mouse{base::mouse_button_code::none};
    type::view_position pos{0.0f, 0.0f};
    mutable bool handled{false};
};

} // namespace sgf

#endif