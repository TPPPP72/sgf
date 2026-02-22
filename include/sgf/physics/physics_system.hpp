#pragma once
#include <chrono>
#include <memory>
#include <sgf/physics/physics_config.hpp>
#include <sgf/type/vec2.hpp>

namespace sgf
{

class game_object;
class event_bus;

class physics_system
{
public:
    physics_system();
    ~physics_system();

    void update(std::chrono::nanoseconds dt, event_bus *eb = nullptr);

    void register_entity(game_object &owner, const physics_config &config);
    void unregister_entity(uint32_t id);

    void apply_linear_impulse(uint32_t id, const type::vec2d &impulse);
    void set_linear_velocity(uint32_t id, const type::vec2d &velocity);
    void sync_to_physics(uint32_t id);

private:
    struct impl;
    std::unique_ptr<impl> p_impl;

    static constexpr float PPM{30.0f};
};

} // namespace sgf