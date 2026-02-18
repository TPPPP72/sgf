#ifndef SGF_GAME_OBJECT_MODULES_MOUSE_MODULE_HPP
#define SGF_GAME_OBJECT_MODULES_MOUSE_MODULE_HPP

#include "../../base/window/window_event.hpp"
#include "base/input_module.hpp"

namespace sgf::module
{

class mouse_module : public base_input_module
{
public:
    using base_input_module::base_input_module;

    void update(std::chrono::nanoseconds dt) override;

    std::chrono::nanoseconds get_time(base::mouse_button_code btn) const noexcept;

    type::view_position position() const noexcept;
    type::view_position delta() const noexcept;

private:
    std::array<std::chrono::nanoseconds, 3> m_timers{};
    type::view_position m_last_pos{0, 0};
    type::view_position m_delta{0, 0};
};

} // namespace sgf::module

#endif