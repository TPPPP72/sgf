#ifndef SGF_FRAME_CONTEXT_HPP
#define SGF_FRAME_CONTEXT_HPP

#include <chrono>
#include <sgf/type/position.hpp>

namespace sgf
{

struct frame_context
{
    std::chrono::nanoseconds dt;
    type::view_position mouse_view_pos;
};

} // namespace sgf

#endif