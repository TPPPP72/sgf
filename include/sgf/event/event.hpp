#ifndef SGF_EVENT_HPP
#define SGF_EVENT_HPP

#include <cstdint>

namespace sgf::event
{

// 对象创建
struct game_object_spawned
{
    std::uint32_t id;
    std::uint32_t hashed_tag;
};

// 对象销毁
struct game_object_destroyed
{
    std::uint32_t id;
    std::uint32_t hashed_tag;
};

// 物理碰撞开始
struct physics_collision_begin
{
    std::uint32_t id_a;
    std::uint32_t hashed_tag_a;
    std::uint32_t id_b;
    std::uint32_t hashed_tag_b;
};

// 物理碰撞结束
struct physics_collision_end
{
    std::uint32_t id_a;
    std::uint32_t hashed_tag_a;
    std::uint32_t id_b;
    std::uint32_t hashed_tag_b;
};

} // namespace sgf::event

#endif