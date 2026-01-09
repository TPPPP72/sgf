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