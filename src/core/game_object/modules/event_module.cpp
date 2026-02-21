#include <sgf/game_object/modules/event_module.hpp>
#include <sgf/scene/scene.hpp>

sgf::event_bus *sgf::module::event_module::bus() const
{
    return this->context().eb;
}