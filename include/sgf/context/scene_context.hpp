#ifndef SGF_SCENE_CONTEXT_HPP
#define SGF_SCENE_CONTEXT_HPP

#include <vector>

namespace sgf
{

class camera;
class physics_system;

namespace event
{
class manager;
}

namespace render
{
class pipeline;
}

namespace resource
{
class manager;
}

struct scene_context
{
    std::vector<camera *> cameras;
    render::pipeline *pipe;
    physics_system *physics;
    event::manager *event_mgr;
    resource::manager *res_mgr;
};

} // namespace sgf

#endif