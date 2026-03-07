#ifndef SGF_ANIMATION_PLAYER_HPP
#define SGF_ANIMATION_PLAYER_HPP

#include <chrono>
#include <sgf/resource/data.hpp>

namespace sgf
{

namespace resource
{
class manager;
}

namespace animation
{

class player
{
public:
    void play(const sgf::resource::animation &);

    void update(std::chrono::nanoseconds dt);

    const sgf::resource::sprite *sprite(sgf::resource::manager &) const;
    std::uint32_t hashed_sprite() const;

private:
    sgf::resource::animation p_anim;

    std::size_t p_frame_index{0};
    std::chrono::nanoseconds p_elapsed{0};
};

} // namespace animation

} // namespace sgf

#endif