#ifndef SGF_BASE_RENDERER_HPP
#define SGF_BASE_RENDERER_HPP

#include "../type/color.hpp"
#include "../type/rect.hpp"
#include "../type/vertex.hpp"
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
    void reset_target();
    void set_clip_rect(const type::view_rect &rect);
    void clear_clip_rect();
    bool is_vsync() const noexcept;
    void set_vsync(bool is_enable);
    bool is_draw_blend() const noexcept;
    void set_draw_blend(bool is_enable);
    sgf::type::color draw_color() const noexcept;
    void set_draw_color(const sgf::type::color &);
    void render_texture(const texture &, const type::resource_rect &src, const type::view_rect &dst);
    void render_texture(const texture &, const type::view_rect &dst);
    void render_texture(const texture &tex, const type::view_position &dst);
    void render_rect(const type::view_rect &, const sgf::type::color &, std::uint8_t style = 0);
    void render_rect(const type::view_rect &, std::uint8_t style = 0);
    void render_geometry(const texture *tex, const type::vertex *vertices, std::int32_t num_vertices, const std::int32_t *indices = nullptr, std::int32_t num_indices = 0);
    void present();

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
    sgf::type::color p_color;
    const viewport *p_viewport_ptr{nullptr};
    bool p_is_vsync{false};
    bool p_is_draw_blend{false};
};

} // namespace sgf::base

#endif