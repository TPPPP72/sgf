#include "../../../include/base/window/window.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>

using namespace sgf::base;

struct window::impl
{
    SDL_Window *window = nullptr;
};

window::window(const window_info &inf) : p_impl(std::make_unique<impl>())
{
    if (!SDL_Init(SDL_INIT_VIDEO))
        throw std::runtime_error(SDL_GetError());

    p_impl->window = SDL_CreateWindow(inf.title.c_str(), inf.width, inf.height, SDL_WINDOW_RESIZABLE);

    if (p_impl->window == nullptr)
        throw std::runtime_error(SDL_GetError());

    p_info = inf;
}

window::~window()
{
    SDL_DestroyWindow(p_impl->window);
}

window_info window::init_info() const noexcept
{
    return p_info;
}

window_info window::current_info() const
{
    window_info inf;
    inf.title = SDL_GetWindowTitle(p_impl->window);

    std::int32_t actual_width, actual_height;
    if (!SDL_GetWindowSize(p_impl->window, &actual_width, &actual_height))
        throw std::runtime_error(SDL_GetError());
    inf.width  = actual_width;
    inf.height = actual_height;

    return inf;
}

void window::poll_event()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            if (p_on_exit == nullptr)
                std::exit(0);

            p_on_exit();
            break;
        }
    }
}

void *window::get() const noexcept
{
    return p_impl->window;
}

std::tuple<std::uint32_t, std::uint32_t> window::init_size() const noexcept
{
    return {p_info.width, p_info.height};
}

std::tuple<std::uint32_t, std::uint32_t> window::current_size() const
{
    std::int32_t w, h;
    if (!SDL_GetWindowSize(p_impl->window, &w, &h))
        throw std::runtime_error(SDL_GetError());

    return {w, h};
}

void window::set_fullscreen(bool is_enable)
{
    if (!SDL_SetWindowFullscreen(p_impl->window, is_enable))
        throw std::runtime_error(SDL_GetError());

    p_is_fullscreen = is_enable;
}

bool window::is_fullscreen() const noexcept
{
    return p_is_fullscreen;
}

void window::on_exit(std::function<void()> f)
{
    p_on_exit = f;
}