#ifndef SGF_BASE_RENDERER_HPP
#define SGF_BASE_RENDERER_HPP

#include "../type/color.hpp"
#include "../type/rect.hpp"
#include "./window/window.hpp"

namespace sgf::base
{

class texture;

class renderer
{
public:
    explicit renderer(const window &);
    ~renderer();
    void             clear();
    void            *get() const noexcept;
    void             set_target(const texture &);
    void             set_target();
    void             set_draw_color(const sgf::type::color &);
    sgf::type::color draw_color() const noexcept;
    void             render_texture(const texture &, const type::rect &src, const type::rect &dst);
    void             render_texture(const texture &, const type::rect &dst);
    void             render_texture(const texture &tex, double x, double y);
    void             render_rect(const type::rect &, const sgf::type::color &);
    void             render_rect(const type::rect &);
    void             present();

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
    sgf::type::color      p_color;
};

} // namespace sgf::base

#endif