#ifndef SGF_GAME_OBJECT_MODULES_CAMERA_MODULE_HPP
#define SGF_GAME_OBJECT_MODULES_CAMERA_MODULE_HPP

#include <sgf/game_object/modules/base/service_module.hpp>
#include <string_view>

namespace sgf
{

class camera;

namespace module
{

class camera_module : public base_service_module
{
public:
    using base_service_module::base_service_module;
    virtual ~camera_module() = default;

    camera *get_main() const;
    camera *get_by_tag(std::string_view tag) const;
};

} // namespace module

} // namespace sgf

#endif