#include <sgf/game_object/modules/keyboard_module.hpp>
#include <sgf/input/input_system.hpp>

void sgf::module::keyboard_module::update(std::chrono::nanoseconds dt)
{
    auto &sys = input_system::instance();

    for (std::uint32_t i = 0; i < m_timers.size(); ++i)
    {
        auto key = static_cast<base::key_code>(i);

        if (sys.is_key_down(key))
            m_timers[i] += dt;
        else
            m_timers[i] = std::chrono::nanoseconds::zero();
    }
}

std::chrono::nanoseconds sgf::module::keyboard_module::get_time(sgf::base::key_code key) const noexcept
{
    auto idx = static_cast<std::uint32_t>(key);
    if (idx < m_timers.size())
        return m_timers[idx];
    return std::chrono::nanoseconds::zero();
}
