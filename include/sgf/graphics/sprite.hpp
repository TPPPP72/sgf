#ifndef SGF_GRAPHICS_SPRITE_HPP
#define SGF_GRAPHICS_SPRITE_HPP

#include "../resources/sprite.hpp"
#include "sgf/type/position.hpp"

namespace sgf::graphics
{

void render(sgf::base::renderer &, const sgf::resources::sprite &, const sgf::type::view_rect &);
void render(sgf::base::renderer &, const sgf::resources::sprite &, const sgf::type::view_position &);

} // namespace sgf::graphics

#endif