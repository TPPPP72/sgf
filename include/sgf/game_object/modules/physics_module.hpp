#ifndef SGF_GAME_OBJECT_MODULES_PHYSICS_MODULE_HPP
#define SGF_GAME_OBJECT_MODULES_PHYSICS_MODULE_HPP

#include <sgf/game_object/modules/base/service_module.hpp>
#include <sgf/physics/physics_config.hpp>
#include <sgf/type/vec2.hpp>

namespace sgf::module
{

class physics_module : public base_service_module
{
public:
    explicit physics_module(game_object &owner, scene_context &context, const physics_config &config);
    ~physics_module() override;

    void apply_linear_impulse(const type::vec2d &impulse);
    void set_linear_velocity(const type::vec2d &velocity);
    void sync_to_physics();
};

} // namespace sgf::module

#endif