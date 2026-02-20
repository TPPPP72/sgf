#include <SDL3/SDL_init.h>
#include <mutex>
#include <sgf/base/guard/video_system.hpp>
#include <stdexcept>

using namespace sgf::base::guard;

video_system::video_system()
{
    static std::once_flag once;
    auto init_video = []()
    {
        if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
            throw std::runtime_error(SDL_GetError());
    };
    std::call_once(once, init_video);
}

video_system::~video_system() = default;