#ifndef SGF_TYPE_RECT_HPP
#define SGF_TYPE_RECT_HPP

#include "base/tags.hpp"

namespace sgf::type
{

template <typename tag>
struct rect
{
    double x, y;
    double w, h;
};

using resource_rect = rect<base::resource_tag>;
using window_rect   = rect<base::window_tag>;
using view_rect     = rect<base::view_tag>;
using world_rect    = rect<base::world_tag>;

} // namespace sgf::type

#endif