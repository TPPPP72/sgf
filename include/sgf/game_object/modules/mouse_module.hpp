#ifndef SGF_GAME_OBJECT_MODULES_MOUSE_MODULE_HPP
#define SGF_GAME_OBJECT_MODULES_MOUSE_MODULE_HPP

#include <array>
#include <sgf/base/window/window_event.hpp>
#include <sgf/context/frame_context.hpp>
#include <sgf/event/input_event.hpp>
#include <sgf/game_object/modules/base/input_module.hpp>

namespace sgf::module
{

class mouse_module : public base_input_module
{
public:
    using base_input_module::base_input_module;
    virtual ~mouse_module() = default;

    void input(const input_event &e) override
    {
        if (e.type == sgf::base::event_type::mouse_button_down)
            m_current_buttons[static_cast<std::size_t>(e.mouse)] = true;
        else if (e.type == sgf::base::event_type::mouse_button_up)
            m_current_buttons[static_cast<std::size_t>(e.mouse)] = false;
    }

    void update(const frame_context &ctx) override
    {
        m_pos          = ctx.mouse_view_pos;
        m_last_buttons = m_current_buttons;
    }

    type::view_position position() const noexcept
    {
        return m_pos;
    }

    bool is_down(base::mouse_button_code btn) const noexcept
    {
        return m_current_buttons[static_cast<std::size_t>(btn)];
    }
    bool is_pressed(base::mouse_button_code btn) const noexcept
    {
        auto b = static_cast<std::size_t>(btn);
        return m_current_buttons[b] && !m_last_buttons[b];
    }
    bool is_released(base::mouse_button_code btn) const noexcept
    {
        auto b = static_cast<std::size_t>(btn);
        return !m_current_buttons[b] && m_last_buttons[b];
    }

private:
    type::view_position m_raw_pos{0.0f, 0.0f};
    type::view_position m_pos{0.0f, 0.0f};

    std::array<bool, 5> m_current_buttons{};
    std::array<bool, 5> m_last_buttons{};
};

} // namespace sgf::module

#endif