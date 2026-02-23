#ifndef SGF_TYPE_POSITION_HPP
#define SGF_TYPE_POSITION_HPP

#include <sgf/type/base/tags.hpp>
#include <sgf/type/vec2.hpp>

namespace sgf::type
{

using window_position = tagged_vec2<float, base::window_tag>;
using view_position   = tagged_vec2<float, base::view_tag>;
using world_position  = tagged_vec2<double, base::world_tag>;

} // namespace sgf::type

#endif