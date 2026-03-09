#include <sgf/context/scene_context.hpp>
#include <sgf/game_object/modules/event_module.hpp>
#include <sgf/scene/scene.hpp>

sgf::event::manager *sgf::module::event_module::manager() const
{
    return this->context().event_mgr;
}