#include "utils/convert.hpp"
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cassert>
#include <sgf/base/surface.hpp>

using namespace sgf::base;

struct surface::impl
{
    SDL_Surface *surface = nullptr;
};

surface::surface(const font &f, const std::string &text, const type::color &color) : p_impl(std::make_unique<impl>())
{
    auto sdl_font = static_cast<TTF_Font *>(f.get());

    SDL_Color c = to_color(color);

    if (text.empty())
        throw std::runtime_error("Can not create a surface from empty string");

    p_impl->surface = TTF_RenderText_Blended(sdl_font, text.c_str(), text.size(), c);

    if (p_impl->surface == nullptr)
        throw std::runtime_error(SDL_GetError());
}

surface::~surface()
{
    SDL_DestroySurface(p_impl->surface);
}

void *surface::get() const noexcept
{
    return p_impl->surface;
}