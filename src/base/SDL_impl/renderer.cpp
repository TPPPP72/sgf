#include "SDL3/SDL_error.h"
#include "sgf/type/rect.hpp"
#include "utils/convert.hpp"
#include <SDL3/SDL_render.h>
#include <sgf/base/renderer.hpp>
#include <sgf/base/texture.hpp>
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

void renderer::reset_target()
{
    if (!SDL_SetRenderTarget(p_impl->renderer, nullptr))
        throw std::runtime_error(SDL_GetError());
}

bool renderer::is_vsync() const noexcept
{
    return p_is_vsync;
}

void renderer::set_vsync(bool is_enable)
{
    if (!SDL_SetRenderVSync(p_impl->renderer, is_enable))
        throw std::runtime_error(SDL_GetError());

    p_is_vsync = is_enable;
}

void renderer::set_clip_rect(const type::view_rect &rect)
{
    SDL_Rect sdl_rect;
    sdl_rect.x = static_cast<std::int32_t>(rect.x);
    sdl_rect.y = static_cast<std::int32_t>(rect.y);
    sdl_rect.w = static_cast<std::int32_t>(rect.w);
    sdl_rect.h = static_cast<std::int32_t>(rect.h);

    if (!SDL_SetRenderClipRect(p_impl->renderer, &sdl_rect))
        throw std::runtime_error(SDL_GetError());
}

void renderer::clear_clip_rect()
{
    if (!SDL_SetRenderClipRect(p_impl->renderer, nullptr))
        throw std::runtime_error(SDL_GetError());
}

bool renderer::is_draw_blend() const noexcept
{
    return p_is_draw_blend;
}

void renderer::set_draw_blend(bool is_enable)
{
    if (!SDL_SetRenderDrawBlendMode(p_impl->renderer, is_enable))
        throw std::runtime_error(SDL_GetError());

    p_is_draw_blend = is_enable;
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

void renderer::render_geometry(const texture *tex, const type::vertex *vertices, std::int32_t num_vertices, const std::int32_t *indices, std::int32_t num_indices)
{
    SDL_Texture *sdl_tex = tex ? static_cast<SDL_Texture *>(tex->get()) : nullptr;

    if (!SDL_RenderGeometry(p_impl->renderer, sdl_tex, reinterpret_cast<const SDL_Vertex *>(vertices), num_vertices, indices, num_indices))
        throw std::runtime_error(SDL_GetError());
}

void renderer::render_texture(const texture &tex, const type::resource_rect &src, const type::view_rect &dst)
{
    if (p_viewport_ptr == nullptr)
        throw std::runtime_error("Please call begin_frame before render");

    auto sdl_texture = static_cast<SDL_Texture *>(tex.get());

    SDL_FRect fr1{to_frect(src)};
    SDL_FRect fr2{to_frect(p_viewport_ptr->to_window_rect(dst))};

    if (!SDL_RenderTexture(p_impl->renderer, sdl_texture, &fr1, &fr2))
        throw std::runtime_error(SDL_GetError());
}

void renderer::render_texture(const texture &tex, const type::view_rect &dst)
{
    if (p_viewport_ptr == nullptr)
        throw std::runtime_error("Please call begin_frame before render");

    auto sdl_texture = static_cast<SDL_Texture *>(tex.get());

    auto fr{to_frect(p_viewport_ptr->to_window_rect(dst))};

    if (!SDL_RenderTexture(p_impl->renderer, sdl_texture, nullptr, &fr))
        throw std::runtime_error(SDL_GetError());
}

void renderer::render_texture(const texture &tex, const type::view_position &dst)
{
    if (p_viewport_ptr == nullptr)
        throw std::runtime_error("Please call begin_frame before render");

    auto sdl_texture = static_cast<SDL_Texture *>(tex.get());

    auto [w, h] = tex.size();

    type::view_rect r{dst.x, dst.y, static_cast<float>(w), static_cast<float>(h)};

    auto fr{to_frect(p_viewport_ptr->to_window_rect(r))};

    if (!SDL_RenderTexture(p_impl->renderer, sdl_texture, nullptr, &fr))
        throw std::runtime_error(SDL_GetError());
}

void renderer::render_rect(const type::view_rect &dst, const type::color &color, std::uint8_t style)
{
    if (p_viewport_ptr == nullptr)
        throw std::runtime_error("Please call begin_frame before render");

    auto temp = this->draw_color();
    this->set_draw_color(color);

    auto fr{to_frect(p_viewport_ptr->to_window_rect(dst))};

    if (style == 0 && !SDL_RenderRect(p_impl->renderer, &fr))
    {
        this->set_draw_color(temp);
        throw std::runtime_error(SDL_GetError());
    }

    if (style == 1 && !SDL_RenderFillRect(p_impl->renderer, &fr))
    {
        this->set_draw_color(temp);
        throw std::runtime_error(SDL_GetError());
    }

    this->set_draw_color(temp);
}

void renderer::render_rect(const type::view_rect &dst, std::uint8_t style)
{
    if (p_viewport_ptr == nullptr)
        throw std::runtime_error("Please call begin_frame before render");

    auto fr{to_frect(p_viewport_ptr->to_window_rect(dst))};

    if (style == 0 && !SDL_RenderRect(p_impl->renderer, &fr))
        throw std::runtime_error(SDL_GetError());

    if (style == 1 && !SDL_RenderFillRect(p_impl->renderer, &fr))
        throw std::runtime_error(SDL_GetError());
}

void *renderer::get() const noexcept
{
    return p_impl->renderer;
}

void renderer::begin_frame(const viewport &vp)
{
    if (p_viewport_ptr != nullptr)
        throw std::runtime_error("Please call end_frame after frame presented");

    set_clip_rect(vp.get_view_rect());
    p_viewport_ptr = &vp;
}

void renderer::end_frame() noexcept
{
    p_viewport_ptr = nullptr;
}