#ifndef SGF_BASE_TRACK_HPP
#define SGF_BASE_TRACK_HPP

#include "audio.hpp"
#include "mixer.hpp"

namespace sgf::base
{

class track
{
public:
    enum class state
    {
        wait_for_audio,
        wait_for_play,
        playing,
        paused
    };

public:
    track(const mixer &);
    ~track();
    void *get() const noexcept;
    void bind_audio(const audio &);
    void play(bool is_loop);
    bool is_playing() const noexcept;
    // when is_playing == false, try play can work
    bool try_play(bool is_loop);
    void pause();
    bool is_paused() const noexcept;
    // when is_pause == false , try paused can work
    bool try_pause();
    void resume();
    bool can_resume() const noexcept;
    // when can_resume == true , try resume can work
    bool try_resume();
    state get_state() const noexcept;
    // check if track has played finished
    void update_state();

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
    const audio *p_audio{nullptr};
    bool p_is_loop{false};
    state p_state{state::wait_for_audio};
};

} // namespace sgf::base

#endif