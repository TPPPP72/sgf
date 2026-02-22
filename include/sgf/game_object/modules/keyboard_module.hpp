#ifndef SGF_GAME_OBJECT_MODULES_KEYBOARD_MODULE_HPP
#define SGF_GAME_OBJECT_MODULES_KEYBOARD_MODULE_HPP

#include <array>
#include <chrono>
#include <sgf/base/window/window_event.hpp>
#include <sgf/context/frame_context.hpp>
#include <sgf/event/input_event.hpp>
#include <sgf/game_object/modules/base/input_module.hpp>

namespace sgf::module
{

class keyboard_module : public base_input_module
{
public:
    using base_input_module::base_input_module;
    virtual ~keyboard_module() = default;

    void input(const input_event &e) override
    {
        if (e.type == sgf::base::event_type::key_down)
            m_current[static_cast<std::size_t>(e.key)] = true;
        else if (e.type == sgf::base::event_type::key_up)
            m_current[static_cast<std::size_t>(e.key)] = false;
    }

    void update(const frame_context &ctx) override
    {
        for (std::size_t i = 0; i < m_current.size(); ++i)
        {
            if (m_current[i])
                m_timers[i] += ctx.dt;
            else
                m_timers[i] = std::chrono::nanoseconds(0);
        }

        m_last = m_current;
    }

    bool is_down(base::key_code key) const noexcept
    {
        return m_current[static_cast<std::size_t>(key)];
    }
    bool is_pressed(base::key_code key) const noexcept
    {
        auto k = static_cast<std::size_t>(key);
        return m_current[k] && !m_last[k];
    }
    bool is_released(base::key_code key) const noexcept
    {
        auto k = static_cast<std::size_t>(key);
        return !m_current[k] && m_last[k];
    }

    std::chrono::nanoseconds get_hold_duration(base::key_code key) const noexcept
    {
        return m_timers[static_cast<std::size_t>(key)];
    }

private:
    std::array<bool, 256> m_current{};
    std::array<bool, 256> m_last{};
    std::array<std::chrono::nanoseconds, 256> m_timers{};
};

} // namespace sgf::module

#endif