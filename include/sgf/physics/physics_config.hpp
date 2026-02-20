#ifndef SGF_PHYSICS_CONFIG_HPP
#define SGF_PHYSICS_CONFIG_HPP

#include <cstdint>
#include <vector>

namespace sgf
{

/**
 * @brief 物理身体类型
 */
enum class body_type : uint8_t
{
    static_body    = 0, // 不受力影响，不可移动（如地面、墙壁）
    kinematic_body = 1, // 不受力影响，但可以通过设置速度移动（如移动平台）
    dynamic_body   = 2  // 完全受物理模拟影响（如玩家、箱子）
};

/**
 * @brief 单个碰撞形状的配置
 */
struct collider_config
{
    // 矩形相对于物体中心点的偏移 (Local Offset)
    float x = 0.0f;
    float y = 0.0f;

    // 矩形的宽度和高度（像素单位，系统内部会除以 PPM）
    float w = 32.0f;
    float h = 32.0f;

    // 物理属性
    float density     = 1.0f; // 密度：影响质量
    float friction    = 0.3f; // 摩擦力：0.0（滑溜）到 1.0（粗糙）
    float restitution = 0.0f; // 弹性：0.0（不弹）到 1.0（完美反弹）

    // 圆形处理
    float radius   = 0.0f; // 如果 > 0，则视为圆形碰撞体
    bool is_circle = false;

    // 传感器模式：如果为 true，只触发碰撞事件但不产生物理碰撞反馈
    bool is_sensor = false;

    // 碰撞过滤
    uint32_t category_bits = 0x0001;
    uint32_t mask_bits     = 0xFFFF;
};

/**
 * @brief 游戏对象完整的物理描述
 */
struct physics_config
{
    body_type type = body_type::static_body;

    // 是否固定旋转（对于横版游戏的玩家，通常设为 true 防止滑倒）
    bool fixed_rotation = false;

    // 允许一个物体拥有多个碰撞形状（组合碰撞体）
    std::vector<collider_config> colliders;

    // 线性阻尼：空气阻力，防止物体在无重力下无限滑动
    float linear_damping  = 0.0f;
    float angular_damping = 0.0f;
};

} // namespace sgf

#endif