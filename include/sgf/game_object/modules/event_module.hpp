#ifndef SGF_GAME_OBJECT_MODULES_EVENT_MODULE_HPP
#define SGF_GAME_OBJECT_MODULES_EVENT_MODULE_HPP

#include "base/service_module.hpp"

namespace sgf
{

class event_bus;

namespace module
{

class event_module : public base_service_module
{
public:
    using base_service_module::base_service_module;
    virtual ~event_module() = default;

    event_bus *event_bus() const;
};

} // namespace module

} // namespace sgf

#endif