#ifndef SGF_INPUT_SYSTEM_HPP
#define SGF_INPUT_SYSTEM_HPP

#include "../base/viewport.hpp"
#include "../base/window/window.hpp"
#include "sgf/base/viewport.hpp"
#include "sgf/type/position.hpp"

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

    void bind_window(base::window *) noexcept;

    void bind_viewport(base::viewport *) noexcept;

    void update();

    bool is_key_pressed(base::key_code) const;
    bool is_key_down(base::key_code) const;
    bool is_key_released(base::key_code) const;

    bool is_button_pressed(base::mouse_button_code) const;
    bool is_button_down(base::mouse_button_code) const;
    bool is_button_released(base::mouse_button_code) const;

    type::window_position get_mouse_window_position() const;
    type::view_position get_mouse_view_position() const;

private:
    input_system()  = default;
    ~input_system() = default;
    base::window_event previous;
    base::window *win{nullptr};
    base::viewport *vp{nullptr};
};

} // namespace sgf

#endif