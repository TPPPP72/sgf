#ifndef SGF_TYPE_VECTOR2_HPP
#define SGF_TYPE_VECTOR2_HPP

#include <sgf/type/base/vector2.hpp>

namespace sgf::type
{

using vec2f = sgf::type::base::vector2<float>;
using vec2d = sgf::type::base::vector2<double>;

template <typename T, typename tag>
struct tagged_vec2 : public sgf::type::base::vector2<T>
{
    using tag_type = tag;
    using vec2     = sgf::type::base::vector2<T>;

    tagged_vec2() = default;
    tagged_vec2(T x, T y) : vec2(x, y) {}
    tagged_vec2(const vec2 &v) : vec2(v) {}
};

} // namespace sgf::type

#endif