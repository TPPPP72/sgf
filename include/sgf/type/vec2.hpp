#ifndef SGF_TYPE_VECTOR2_HPP
#define SGF_TYPE_VECTOR2_HPP

#include "base/vector2.hpp"

namespace sgf::type
{

using vec2 = sgf::type::base::vector2<double>;

template <typename tag>
struct tagged_vec2 : public vec2
{
    using tag_type = tag;

    tagged_vec2() = default;
    tagged_vec2(double x, double y) : vec2(x, y) {}
    tagged_vec2(const vec2 &v) : vec2(v) {}
};

} // namespace sgf::type

#endif