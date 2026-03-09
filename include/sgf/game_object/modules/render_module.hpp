#ifndef SGF_GAME_OBJECT_MODULES_RENDER_MODULE_HPP
#define SGF_GAME_OBJECT_MODULES_RENDER_MODULE_HPP

#include <sgf/game_object/modules/base/service_module.hpp>

namespace sgf
{

namespace render
{
class pipeline;
}

namespace module
{

class render_module : public base_service_module
{
public:
    using base_service_module::base_service_module;
    virtual ~render_module() = default;

    render::pipeline *pipeline() noexcept;
};

} // namespace module

} // namespace sgf

#endif