#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <sgf/base/texture.hpp>
#include <stdexcept>

using namespace sgf::base;

struct texture::impl
{
    SDL_Texture *texture = nullptr;
};

texture::texture(const renderer &rend, std::uint32_t width, std::uint32_t height) : p_impl(std::make_unique<impl>())
{
    auto sdl_renderer = static_cast<SDL_Renderer *>(rend.get());

    p_impl->texture = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

    if (p_impl->texture == nullptr)
        throw std::runtime_error(SDL_GetError());
}

texture::texture(const renderer &rend, const std::filesystem::path &p) : p_impl(std::make_unique<impl>())
{
    auto sdl_renderer = static_cast<SDL_Renderer *>(rend.get());

    p_impl->texture = IMG_LoadTexture(sdl_renderer, p.string().c_str());

    if (p_impl->texture == nullptr)
        throw std::runtime_error(SDL_GetError());
}

texture::texture(const renderer &rend, const surface &surf) : p_impl(std::make_unique<impl>())
{
    auto sdl_renderer = static_cast<SDL_Renderer *>(rend.get());

    auto sdl_surface = static_cast<SDL_Surface *>(surf.get());

    p_impl->texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_surface);

    if (p_impl->texture == nullptr)
        throw std::runtime_error(SDL_GetError());
}

texture::texture(const renderer &rend, const font &f, const std::string &text, const type::color &color) : p_impl(std::make_unique<impl>())
{
    auto sdl_renderer = static_cast<SDL_Renderer *>(rend.get());

    auto temp_surface = surface{f, text, color};
    auto sdl_surface  = static_cast<SDL_Surface *>(temp_surface.get());

    p_impl->texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_surface);

    if (p_impl->texture == nullptr)
        throw std::runtime_error(SDL_GetError());
}

texture::~texture()
{
    SDL_DestroyTexture(p_impl->texture);
}

void *texture::get() const noexcept
{
    return p_impl->texture;
}

sgf::type::resource_size texture::size() const
{
    float _w, _h;
    if (!SDL_GetTextureSize(p_impl->texture, &_w, &_h))
        throw std::runtime_error(SDL_GetError());

    return {static_cast<std::uint32_t>(_w), static_cast<std::uint32_t>(_h)};
}