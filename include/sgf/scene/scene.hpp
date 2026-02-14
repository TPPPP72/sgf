#ifndef SGF_SCENE_HPP
#define SGF_SCENE_HPP

#include "../base/renderer.hpp"
#include <chrono>

namespace sgf
{

class scene
{
public:
    virtual ~scene()                                 = default;
    virtual void init()                              = 0;
    virtual void update(std::chrono::nanoseconds dt) = 0;
    virtual void render(base::renderer &)            = 0;

    bool should_update{true};
    bool should_render{true};
    std::string id{""};
};

} // namespace sgf

#endif