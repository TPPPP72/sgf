#include <sgf/game_object/modules/mouse_module.hpp>
#include <sgf/input/input_system.hpp>

void sgf::module::mouse_module::update(std::chrono::nanoseconds dt)
{
    auto &sys = input_system::instance();

    for (std::uint32_t i = 0; i < m_timers.size(); ++i)
    {
        auto btn = static_cast<base::mouse_button_code>(i);

        if (sys.is_button_down(btn))
            m_timers[i] += dt;
        else
            m_timers[i] = std::chrono::nanoseconds::zero();
    }

    auto current_pos = sys.get_mouse_view_position();

    m_delta.x = current_pos.x - m_last_pos.x;
    m_delta.y = current_pos.y - m_last_pos.y;

    m_last_pos = current_pos;
}

std::chrono::nanoseconds sgf::module::mouse_module::get_time(sgf::base::mouse_button_code btn) const noexcept
{
    auto idx = static_cast<std::uint32_t>(btn);
    return (idx < m_timers.size()) ? m_timers[idx] : std::chrono::nanoseconds::zero();
}

sgf::type::view_position sgf::module::mouse_module::position() const noexcept
{
    return m_last_pos;
}

sgf::type::view_position sgf::module::mouse_module::delta() const noexcept
{
    return m_delta;
}