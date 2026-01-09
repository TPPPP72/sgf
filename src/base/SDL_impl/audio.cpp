#include <SDL3_mixer/SDL_mixer.h>
#include <sgf/base/audio/audio.hpp>

using namespace sgf::base;

struct audio::impl
{
    MIX_Audio *audio = nullptr;
};

audio::audio(const std::filesystem::path &p) : p_impl(std::make_unique<impl>())
{
    auto audio = MIX_LoadAudio(nullptr, p.string().c_str(), false);
    if (audio == nullptr)
        throw std::runtime_error(SDL_GetError());

    SDL_PropertiesID props  = MIX_GetAudioProperties(audio);
    int frames              = SDL_GetNumberProperty(props, MIX_PROP_METADATA_DURATION_FRAMES_NUMBER, 0);
    double duration_seconds = 0.0;
    if (frames > 0)
    {
        int sample_rate  = 48000;
        duration_seconds = static_cast<double>(frames) / sample_rate;
    }
    bool predecode = duration_seconds <= 10.0;
    MIX_DestroyAudio(audio);
    SDL_DestroyProperties(props);

    p_impl->audio = MIX_LoadAudio(nullptr, p.string().c_str(), predecode);
    if (p_impl->audio)
        throw std::runtime_error(SDL_GetError());
}

audio::~audio()
{
    MIX_DestroyAudio(p_impl->audio);
}

void *audio::get() const noexcept
{
    return p_impl->audio;
}