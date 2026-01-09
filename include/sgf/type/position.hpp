#ifndef SGF_TYPE_POSITION_HPP
#define SGF_TYPE_POSITION_HPP

#include "base/tags.hpp"
#include "vec2.hpp"

namespace sgf::type
{

using window_position = tagged_vec2<base::window_tag>;
using view_position   = tagged_vec2<base::view_tag>;
using world_position  = tagged_vec2<base::world_tag>;

} // namespace sgf::type

#endif