#ifndef SGF_BASE_VIEWPORT_HPP
#define SGF_BASE_VIEWPORT_HPP

#include "../type/rect.hpp"
#include "../type/size.hpp"
#include "window/window.hpp"

namespace sgf::base
{

class viewport
{
public:
    explicit viewport(const window &win, const type::view_size &init_vs) : p_window(win), p_view_size(init_vs)
    {
    }
    ~viewport() = default;
    inline void update()
    {
        auto window_size = p_window.current_size();

        auto sx = static_cast<double>(window_size.w) / p_view_size.w;
        auto sy = static_cast<double>(window_size.h) / p_view_size.h;

        p_scale = std::min(sx, sy);

        auto real_w = p_view_size.w * p_scale;
        auto real_h = p_view_size.h * p_scale;

        p_offset.x = (window_size.w - real_w) / 2.0;
        p_offset.y = (window_size.h - real_h) / 2.0;
    }
    type::view_rect get_view_rect() const noexcept
    {
        return {p_offset.x, p_offset.y, p_view_size.w * p_scale, p_view_size.h * p_scale};
    }
    inline type::view_rect to_view_rect(const type::window_rect &wr) const noexcept
    {
        return {(wr.x - p_offset.x) / p_scale, (wr.y - p_offset.y) / p_scale, wr.w / p_scale, wr.h / p_scale};
    }
    type::window_rect to_window_rect(const type::view_rect &vr) const noexcept
    {
        return {p_offset.x + vr.x * p_scale, p_offset.y + vr.y * p_scale, vr.w * p_scale, vr.h * p_scale};
    }
    type::view_position to_view_position(const type::window_position &wp) const noexcept
    {
        return {(wp.x - p_offset.x) / p_scale, (wp.y - p_offset.y) / p_scale};
    }
    type::window_position to_window_position(const type::view_position &vp) const noexcept
    {
        return {p_offset.x + vp.x * p_scale, p_offset.y + vp.y * p_scale};
    }
    void set_view_size(const type::view_size &vs)
    {
        p_view_size = vs;
        update();
    }

private:
    const window &p_window;
    type::view_size p_view_size;
    type::window_position p_offset;
    double p_scale{1.0};
};

} // namespace sgf::base

#endif