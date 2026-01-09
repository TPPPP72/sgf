#include <SDL3_ttf/SDL_ttf.h>
#include <mutex>
#include <sgf/base/guard/font_system.hpp>
#include <stdexcept>

using namespace sgf::base::guard;

font_system::font_system()
{
    static std::once_flag once;
    auto init_font = []()
    {
        if (!TTF_Init())
            throw std::runtime_error(SDL_GetError());
    };
    std::call_once(once, init_font);
}

font_system::~font_system() = default;