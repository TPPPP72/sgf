#ifndef SGF_ANIMATION_CLIP_HPP
#define SGF_ANIMATION_CLIP_HPP

#include "../resources/sprite.hpp"

namespace sgf::animation
{

struct clip
{
    std::vector<const resources::sprite *> frames;
    std::chrono::nanoseconds frame_duration;
    bool loop = true;
};

} // namespace sgf::animation

#endif