#ifndef SGF_TYPE_RECT_HPP
#define SGF_TYPE_RECT_HPP

#include <sgf/type/base/tags.hpp>

namespace sgf::type
{

template <typename T, typename tag>
struct rect
{
    T x, y;
    T w, h;
};

using resource_rect = rect<float, base::resource_tag>;
using window_rect   = rect<float, base::window_tag>;
using view_rect     = rect<float, base::view_tag>;
using world_rect    = rect<double, base::world_tag>;

} // namespace sgf::type

#endif