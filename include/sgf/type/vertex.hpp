#ifndef SGF_TYPE_VERTEX
#define SGF_TYPE_VERTEX

#include "color.hpp"
#include "vec2.hpp"

namespace sgf::type
{

struct vertex
{
    vec2f position;
    colorf color;
    vec2f uv;
};

} // namespace sgf::type

#endif