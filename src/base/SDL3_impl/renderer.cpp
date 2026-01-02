#include "../../../include/sgf/base/renderer.hpp"
#include "../../../include/sgf/base/texture.hpp"
#include "utils/convert.hpp"
#include <SDL3/SDL_render.h>
#include <stdexcept>

using namespace sgf::base;

struct renderer::impl
{
    SDL_Renderer *renderer = nullptr;
};

renderer::renderer(const window &win) : p_impl(std::make_unique<impl>())
{
    auto sdl_window = static_cast<SDL_Window *>(win.get());

    p_impl->renderer = SDL_CreateRenderer(sdl_window, nullptr);

    if (p_impl->renderer == nullptr)
        throw std::runtime_error(SDL_GetError());
}

renderer::~renderer()
{
    SDL_DestroyRenderer(p_impl->renderer);
}

void renderer::clear()
{
    if (!SDL_RenderClear(p_impl->renderer))
        throw std::runtime_error(SDL_GetError());
}

void renderer::set_target(const texture &tex)
{
    auto sdl_texture = static_cast<SDL_Texture *>(tex.get());

    if (!SDL_SetRenderTarget(p_impl->renderer, sdl_texture))
        throw std::runtime_error(SDL_GetError());
}

void renderer::set_target()
{
    if (!SDL_SetRenderTarget(p_impl->renderer, nullptr))
        throw std::runtime_error(SDL_GetError());
}

void renderer::set_draw_color(const type::color &color)
{
    if (!SDL_SetRenderDrawColor(p_impl->renderer, color.r, color.g, color.b, color.a))
        throw std::runtime_error(SDL_GetError());

    p_color = color;
}

sgf::type::color renderer::draw_color() const noexcept
{
    return p_color;
}

void renderer::present()
{
    if (!SDL_RenderPresent(p_impl->renderer))
        throw std::runtime_error(SDL_GetError());
}

void renderer::render_texture(const texture &tex, const type::rect &src, const type::rect &dst)
{
    auto sdl_texture = static_cast<SDL_Texture *>(tex.get());

    auto fr1{to_frect(src)};
    auto fr2{to_frect(dst)};

    if (!SDL_RenderTexture(p_impl->renderer, sdl_texture, &fr1, &fr2))
        throw std::runtime_error(SDL_GetError());
}

void renderer::render_texture(const texture &tex, const type::rect &dst)
{
    auto sdl_texture = static_cast<SDL_Texture *>(tex.get());

    auto fr{to_frect(dst)};

    if (!SDL_RenderTexture(p_impl->renderer, sdl_texture, nullptr, &fr))
        throw std::runtime_error(SDL_GetError());
}

void renderer::render_texture(const texture &tex, double x, double y)
{
    auto sdl_texture = static_cast<SDL_Texture *>(tex.get());

    auto [w, h] = tex.size();

    type::rect r{x, y, w, h};

    SDL_FRect fr = to_frect(r);

    if (!SDL_RenderTexture(p_impl->renderer, sdl_texture, nullptr, &fr))
        throw std::runtime_error(SDL_GetError());
}

void renderer::render_rect(const type::rect &dst, const type::color &color)
{
    auto temp = this->draw_color();
    this->set_draw_color(color);

    auto fr = to_frect(dst);

    if (!SDL_RenderRect(p_impl->renderer, &fr))
    {
        this->set_draw_color(temp);
        throw std::runtime_error(SDL_GetError());
    }

    this->set_draw_color(temp);
}

void renderer::render_rect(const type::rect &dst)
{
    auto fr = to_frect(dst);

    if (!SDL_RenderRect(p_impl->renderer, &fr))
        throw std::runtime_error(SDL_GetError());
}

void *renderer::get() const noexcept
{
    return p_impl->renderer;
}