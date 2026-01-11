#include "SDL3/SDL_error.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <sgf/base/audio/track.hpp>
#include <stdexcept>

using namespace sgf::base;

struct track::impl
{
    MIX_Track *track;
};

track::track(const mixer &mix) : p_impl(std::make_unique<impl>())
{
    p_impl->track = MIX_CreateTrack(static_cast<MIX_Mixer *>(mix.get()));

    if (p_impl->track == nullptr)
        throw std::runtime_error(SDL_GetError());
}

track::~track()
{
    MIX_DestroyTrack(p_impl->track);
}

void *track::get() const noexcept
{
    return p_impl->track;
}

void track::bind_audio(const audio &aud)
{
    p_audio = &aud;

    if (!MIX_SetTrackAudio(p_impl->track, static_cast<MIX_Audio *>(p_audio->get())))
        throw std::runtime_error(SDL_GetError());

    p_state = state::wait_for_play;
}

void track::play(bool is_loop)
{
    if (p_state != state::wait_for_play)
        throw std::runtime_error("Can not play a track before bind_audio");

    auto props{SDL_CreateProperties()};
    SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, is_loop ? -1 : 0);

    if (!MIX_PlayTrack(p_impl->track, props))
    {
        SDL_DestroyProperties(props); // none raii object should be released when throw error
        throw std::runtime_error(SDL_GetError());
    }

    SDL_DestroyProperties(props);

    p_state = state::playing;
}

bool track::is_playing() const noexcept
{
    return p_state == state::playing;
}

bool track::try_play(bool is_loop)
{
    if (is_playing())
        return false;

    play(is_loop);
    return true;
}

void track::pause()
{
    if (p_state != state::playing)
        throw std::runtime_error("Can not pause a track not playing");

    if (!MIX_PauseTrack(p_impl->track))
        throw std::runtime_error(SDL_GetError());

    p_state = state::paused;
}

bool track::is_paused() const noexcept
{
    return p_state == state::paused;
}

bool track::try_pause()
{
    if (is_paused())
        return false;

    pause();
    return true;
}

void track::resume()
{
    if (p_state != state::paused)
        throw std::runtime_error("Can not resume a track not paused");

    if (!MIX_ResumeTrack(p_impl->track))
        throw std::runtime_error(SDL_GetError());

    p_state = state::playing;
}

bool track::can_resume() const noexcept
{
    return p_state == state::paused;
}

bool track::try_resume()
{
    if (!can_resume())
        return false;

    resume();
    return true;
}

track::state track::get_state() const noexcept
{
    return p_state;
}

void track::update_state()
{
    if (!MIX_TrackPlaying(p_impl->track) && p_audio != nullptr)
        p_state = state::wait_for_play;
}