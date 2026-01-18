#ifndef SGF_ANIMATION_PLAYER_HPP
#define SGF_ANIMATION_PLAYER_HPP

#include "clip.hpp"

namespace sgf::animation
{

class player
{
public:
    void play(const clip *);

    void update(std::chrono::nanoseconds dt);

    const resources::sprite &current_sprite() const;

private:
    const clip *p_clip = nullptr;

    std::size_t p_frame_index = 0;
    std::chrono::nanoseconds p_elapsed{0};
};

} // namespace sgf::animation

#endif