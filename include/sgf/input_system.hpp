#ifndef SGF_INPUT_SYSTEM_HPP
#define SGF_INPUT_SYSTEM_HPP

#include "base/window/window.hpp"

namespace sgf
{

class input_system
{
public:
    input_system(const input_system &)            = delete;
    input_system &operator=(const input_system &) = delete;
    input_system(input_system &&)                 = delete;
    input_system &operator=(input_system &&)      = delete;

    static input_system &instance() noexcept;

    void bind(base::window *) noexcept;

    void update();

    bool is_key_pressed(base::key_code) const;
    bool is_key_down(base::key_code) const;
    bool is_key_released(base::key_code) const;

    bool is_button_pressed(base::mouse_button_code) const;
    bool is_button_down(base::mouse_button_code) const;
    bool is_button_released(base::mouse_button_code) const;

    type::window_position get_mouse_position() const;

private:
    input_system()  = default;
    ~input_system() = default;
    base::window_event previous;
    base::window *win{nullptr};
    bool has_call_update{false};
};

} // namespace sgf

#endif