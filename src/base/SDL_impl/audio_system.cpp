#include <SDL3/SDL_init.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <mutex>
#include <sgf/base/guard/audio_system.hpp>
#include <stdexcept>

using namespace sgf::base::guard;

audio_system::audio_system()
{
    static std::once_flag once;
    auto init_audio = []()
    {
        if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
            throw std::runtime_error(SDL_GetError());

        if (!MIX_Init())
            throw std::runtime_error(SDL_GetError());
    };
    std::call_once(once, init_audio);
}

audio_system::~audio_system() = default;