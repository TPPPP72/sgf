#include <SDL3_mixer/SDL_mixer.h>
#include <sgf/base/audio/mixer.hpp>
#include <stdexcept>

using namespace sgf::base;

struct mixer::impl
{
    MIX_Mixer *mixer = nullptr;
};

mixer::mixer() : p_impl(std::make_unique<impl>())
{
    p_impl->mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

    if (p_impl->mixer == nullptr)
        throw std::runtime_error(SDL_GetError());
}

mixer::~mixer()
{
    MIX_DestroyMixer(p_impl->mixer);
}

void *mixer::get() const noexcept
{
    return p_impl->mixer;
}