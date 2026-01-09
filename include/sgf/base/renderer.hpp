#ifndef SGF_BASE_RENDERER_HPP
#define SGF_BASE_RENDERER_HPP

#include "../type/color.hpp"
#include "../type/rect.hpp"
#include "viewport.hpp"
#include "window/window.hpp"

namespace sgf::base
{

class texture;

class renderer
{
public:
    explicit renderer(const window &);
    ~renderer();
    void begin_frame(const viewport &);
    void end_frame() noexcept;
    void clear();
    void *get() const noexcept;
    void set_target(const texture &);
    void set_target();
    void set_draw_color(const sgf::type::color &);
    sgf::type::color draw_color() const noexcept;
    void render_texture(const texture &, const type::resource_rect &src, const type::view_rect &dst);
    void render_texture(const texture &, const type::view_rect &dst);
    void render_texture(const texture &tex, const type::view_position &dst);
    void render_rect(const type::view_rect &, const sgf::type::color &);
    void render_rect(const type::view_rect &);
    void present();

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
    sgf::type::color p_color;
    const viewport *p_viewport_ptr{nullptr};
};

} // namespace sgf::base

#endif