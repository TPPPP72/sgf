#ifndef SGF_EVENT_HPP
#define SGF_EVENT_HPP

#include <cstdint>
#include <string>

namespace sgf::event
{

// 碰撞开始
struct collision_begin
{
    std::uint32_t id_a;
    std::uint32_t id_b;

    // 碰撞强度
    float manifold_normal_impulse;
};

// 碰撞结束
struct collision_end
{
    std::uint32_t id_a;
    std::uint32_t id_b;
};

// 对象创建
struct entity_spawned
{
    std::uint32_t entity_id;
    std::string tag; // "enemy", "ball", etc.
};

// 对象销毁
struct entity_destroyed
{
    std::uint32_t entity_id;
};

// 触发器
struct trigger_entered
{
    uint32_t trigger_id;
    uint32_t traveler_id;
};

} // namespace sgf::event

#endif