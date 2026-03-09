#ifndef SGF_GAME_OBJECT_MODULES_EVENT_MODULE_HPP
#define SGF_GAME_OBJECT_MODULES_EVENT_MODULE_HPP

#include <sgf/game_object/modules/base/service_module.hpp>

namespace sgf
{

namespace event
{
class manager;
}

namespace module
{

class event_module : public base_service_module
{
public:
    using base_service_module::base_service_module;
    virtual ~event_module() = default;

    event::manager *manager() const;
};

} // namespace module

} // namespace sgf

#endif