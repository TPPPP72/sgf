#ifndef SGF_GAME_OBJECT_MODULES_KEYBOARD_MODULE_HPP
#define SGF_GAME_OBJECT_MODULES_KEYBOARD_MODULE_HPP

#include "../../base/window/window_event.hpp"
#include "base/input_module.hpp"

namespace sgf::module
{

class keyboard_module : public base_input_module
{
public:
    using base_input_module::base_input_module;
    virtual ~keyboard_module() = default;

    void update(std::chrono::nanoseconds dt) override;

    std::chrono::nanoseconds get_time(base::key_code key) const noexcept;

private:
    std::array<std::chrono::nanoseconds, 231> m_timers{};
};

} // namespace sgf::module

#endif