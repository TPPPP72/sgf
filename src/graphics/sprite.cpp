#include <sgf/base/renderer.hpp>
#include <sgf/graphics/sprite.hpp>
#include <sgf/type/position.hpp>

void sgf::graphics::render(sgf::base::renderer &rd, const sgf::resources::sprite &s, const sgf::type::view_rect &dst)
{
    if (!s.texture_ptr)
        return;

    rd.render_texture(*s.texture_ptr, s.rect, dst);
}

void sgf::graphics::render(sgf::base::renderer &rd, const sgf::resources::sprite &s, const sgf::type::view_position &dst)
{
    if (!s.texture_ptr)
        return;

    double dst_x = dst.x - s.rect.w * s.pivot.x;
    double dst_y = dst.y - s.rect.h * s.pivot.y;

    sgf::type::view_rect dst_rect{dst_x, dst_y, s.rect.w, s.rect.h};

    rd.render_texture(*s.texture_ptr, s.rect, dst_rect);
}