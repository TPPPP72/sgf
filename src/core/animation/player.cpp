#include <sgf/animation/player.hpp>
#include <sgf/resource/manager.hpp>

void sgf::animation::player::play(const sgf::resource::animation &anim)
{
    p_frame_index = 0;
    p_elapsed     = std::chrono::nanoseconds::zero();
    p_anim        = anim;
}

void sgf::animation::player::update(std::chrono::nanoseconds dt)
{
    if (p_anim.frames.empty())
        return;

    p_elapsed += dt;
    auto p_elapsed_ms = std::chrono::duration<float, std::milli>(dt).count();

    while (p_elapsed_ms >= p_anim.frames[p_frame_index].msec)
    {
        p_elapsed_ms -= p_anim.frames[p_frame_index].msec;
        ++p_frame_index;

        if (p_frame_index >= p_anim.frames.size())
            p_frame_index = 0;
    }
}

const sgf::resource::sprite *sgf::animation::player::sprite(sgf::resource::manager &manager) const
{
    return manager.get<resource::sprite>(p_anim.frames[p_frame_index].sprite);
}

std::uint32_t sgf::animation::player::hashed_sprite() const
{
    return p_anim.frames[p_frame_index].sprite;
}
