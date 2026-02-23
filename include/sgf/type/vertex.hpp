#ifndef SGF_TYPE_VERTEX
#define SGF_TYPE_VERTEX

#include <sgf/type/color.hpp>
#include <sgf/type/vec2.hpp>

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