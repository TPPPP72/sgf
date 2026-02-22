#ifndef SGF_SCENE_CONTEXT_HPP
#define SGF_SCENE_CONTEXT_HPP

#include <vector>

namespace sgf
{

class camera;
class render_pipeline;
class physics_system;
class event_bus;

struct scene_context
{
    std::vector<camera *> cameras;
    render_pipeline *pipeline;
    physics_system *physics;
    event_bus *eb;
};

} // namespace sgf

#endif