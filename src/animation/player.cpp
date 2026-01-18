#include <sgf/animation/player.hpp>

using namespace sgf::animation;

void player::play(const clip *cl)
{
    p_clip = cl;
}

void player::update(std::chrono::nanoseconds dt)
{
    if (!p_clip || p_clip->frames.empty())
        return;

    p_elapsed += dt;

    while (p_elapsed >= p_clip->frame_duration)
    {
        p_elapsed -= p_clip->frame_duration;
        ++p_frame_index;

        if (p_frame_index >= p_clip->frames.size())
        {
            if (p_clip->loop)
                p_frame_index = 0;
            else
                p_frame_index = p_clip->frames.size() - 1;
        }
    }
}

const sgf::resources::sprite &player::current_sprite() const
{
    return *p_clip->frames[p_frame_index];
}