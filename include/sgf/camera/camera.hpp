#ifndef SGF_CAMERA_HPP
#define SGF_CAMERA_HPP

#include "../type/position.hpp"
#include "../type/rect.hpp"
#include "../type/size.hpp"
#include <algorithm>

namespace sgf
{

class camera
{
public:
    camera(const type::view_size vs, const type::world_size ws) : p_view_size(vs), p_world_size(ws), p_world_position(0, 0) {}
    type::world_position position() const noexcept
    {
        return p_world_position;
    }
    void set_position(const type::world_position pos)
    {
        auto target_x = pos.x - p_view_size.w / 2.0;
        auto target_y = pos.y - p_view_size.h / 2.0;

        p_world_position.x = std::max(0.0, std::min(target_x, static_cast<double>(p_world_size.w - p_view_size.w)));
        p_world_position.y = std::max(0.0, std::min(target_y, static_cast<double>(p_world_size.h - p_view_size.h)));
    }
    type::view_position to_view_pos(const type::world_position pos) const noexcept
    {
        return {static_cast<float>(pos.x - p_world_position.x), static_cast<float>(pos.y - p_world_position.y)};
    }
    type::view_rect to_view_rect(const type::world_rect rect) const noexcept
    {
        return {
            static_cast<float>(rect.x - p_world_position.x),
            static_cast<float>(rect.y - p_world_position.y),
            static_cast<float>(rect.w),
            static_cast<float>(rect.h)};
    }

private:
    type::view_size p_view_size;
    type::world_size p_world_size;
    type::world_position p_world_position;
};

} // namespace sgf

#endif