#ifndef SGF_VIEW_HPP
#define SGF_VIEW_HPP

#include <cstdint>
#include <memory>
#include <sgf/type/position.hpp>
#include <sgf/type/rect.hpp>

namespace sgf
{

class input_event;
class frame_context;
class ui_manager;

namespace render
{
class pipeline;
}

class view : public std::enable_shared_from_this<view>
{
public:
    virtual ~view() = default;

    std::int16_t z_index{2000};

    view &set_pos(float x, float y)
    {
        m_view_rect.x = x;
        m_view_rect.y = y;
        return *this;
    }
    view &set_size(float w, float h)
    {
        m_view_rect.w = w;
        m_view_rect.h = h;
        return *this;
    }

    bool is_active() const noexcept
    {
        return m_is_visible && m_is_enabled;
    }

    void set_enabled(bool enabled) { m_is_enabled = enabled; }
    void set_visible(bool visible) { m_is_visible = visible; }

protected:
    const type::view_rect &view_rect() const noexcept
    {
        return m_view_rect;
    }

    virtual bool is_inside(const type::view_position &pos) const
    {
        return pos.x >= m_view_rect.x && pos.x <= m_view_rect.x + m_view_rect.w &&
               pos.y >= m_view_rect.y && pos.y <= m_view_rect.y + m_view_rect.h;
    }

    virtual bool on_input(const input_event &ev)
    {
        return false;
    }

    virtual void on_focus_changed(bool has_focus) {}
    virtual void on_mouse_enter() {}
    virtual void on_mouse_leave() {}
    virtual void on_update(const frame_context &) {}
    virtual void on_render(render::pipeline &) {}
    ui_manager *p_manager = nullptr;
    friend class ui_manager;

private:
    bool m_is_visible{true};
    bool m_is_enabled{true};
    type::view_rect m_view_rect;
};

} // namespace sgf

#endif