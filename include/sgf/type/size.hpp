#ifndef SGF_TYPE_SIZE_HPP
#define SGF_TYPE_SIZE_HPP

#include <sgf/type/base/tags.hpp>
#include <sgf/type/int.hpp>

namespace sgf::type
{

template <typename tag>
struct size
{
    uint32 w, h;
};

using resource_size = size<base::resource_tag>;
using window_size   = size<base::window_tag>;
using view_size     = size<base::view_tag>;
using world_size    = size<base::world_tag>;

} // namespace sgf::type

#endif