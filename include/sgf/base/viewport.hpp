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
    explicit viewport(const window &win) : p_window(&win), p_view_size({win.init_size().w, win.init_size().h})
    {
    }
    ~viewport() = default;
    inline void update()
    {
#ifdef SGF_TEST
        auto window_size = test_window_size;
#else
        auto window_size = p_window->current_size();
#endif

        auto sx = static_cast<double>(window_size.w) / p_view_size.w;
        auto sy = static_cast<double>(window_size.h) / p_view_size.h;

        p_scale = std::min(sx, sy);

        auto real_w = p_view_size.w * p_scale;
        auto real_h = p_view_size.h * p_scale;

        p_offset.x = (window_size.w - real_w) / 2.0;
        p_offset.y = (window_size.h - real_h) / 2.0;
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

private:
    const window *p_window{nullptr};
    type::view_size p_view_size;
    type::window_position p_offset;
    double p_scale{1.0};

#ifdef SGF_TEST

public:
    viewport(type::window_size ws, type::view_size vs)
        : test_window_size(ws), p_view_size(vs)
    {
    }
    double get_scale() const { return p_scale; }
    type::window_position get_offset() const { return p_offset; }
    type::view_size get_view_size() const { return p_view_size; }

private:
    type::window_size test_window_size{0, 0};

#endif
};

} // namespace sgf::base

#endif