#ifndef SGF_RESOURCES_SPRITE_HPP
#define SGF_RESOURCES_SPRITE_HPP

#include "../base/texture.hpp"
#include "../type/rect.hpp"
#include "../type/vec2.hpp"

namespace sgf::resources
{

struct sprite
{
    sprite(const base::texture *ptr, const type::resource_rect &rt, const type::vec2 &vec) : texture_ptr(ptr), rect(rt), pivot(vec) {}
    const base::texture *texture_ptr{nullptr};
    type::resource_rect rect{0, 0, 0, 0};
    type::vec2 pivot{0.5, 0.5};
};

} // namespace sgf::resources

#endif