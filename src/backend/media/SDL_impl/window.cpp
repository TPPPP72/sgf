#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <sgf/base/window/window.hpp>
#include <sgf/base/window/window_event.hpp>
#include <stdexcept>

using namespace sgf::base;

struct window::impl
{
    SDL_Window *window = nullptr;
};

window::window(const window_info &inf) : p_impl(std::make_unique<impl>())
{
    p_impl->window = SDL_CreateWindow(inf.title.c_str(), inf.size.w, inf.size.h, SDL_WINDOW_RESIZABLE);

    if (p_impl->window == nullptr)
        throw std::runtime_error(SDL_GetError());

    p_info               = inf;
    p_current_event.type = event_type::current;
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
    inf.size.w = actual_width;
    inf.size.h = actual_height;

    return inf;
}

void window::poll_events()
{
    p_events.clear();
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        window_event e;
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            if (p_on_exit == nullptr)
                std::exit(0);

            p_on_exit();
            break;

        case SDL_EVENT_WINDOW_RESIZED:
        case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
            if (p_on_resize != nullptr)
                p_on_resize();
            break;

        case SDL_EVENT_KEY_DOWN:
            e.type = event_type::key_down;
            e.key  = static_cast<key_code>(event.key.scancode);
            break;

        case SDL_EVENT_KEY_UP:
            e.type = event_type::key_up;
            e.key  = static_cast<key_code>(event.key.scancode);
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            e.type  = event_type::mouse_button_down;
            e.mouse = static_cast<mouse_button_code>(event.button.button);
            e.pos.x = event.motion.x;
            e.pos.y = event.motion.y;
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            e.type  = event_type::mouse_button_up;
            e.mouse = static_cast<mouse_button_code>(event.button.button);
            e.pos.x = event.motion.x;
            e.pos.y = event.motion.y;
            break;

        case SDL_EVENT_MOUSE_MOTION:
            p_current_event.pos.x = event.motion.x;
            p_current_event.pos.y = event.motion.y;
            break;
        }
        if (e.type != event_type::none)
            p_events.emplace_back(e);
    }
}

window_event window::current_event() const noexcept
{
    return p_current_event;
}

std::vector<window_event> window::events() const noexcept
{
    return p_events;
}

void *window::get() const noexcept
{
    return p_impl->window;
}

std::string window::init_title() const noexcept
{
    return p_info.title;
}

std::string window::current_title() const noexcept
{
    return SDL_GetWindowTitle(p_impl->window);
}

void window::set_title(const std::string &title)
{
    if (!SDL_SetWindowTitle(p_impl->window, title.c_str()))
        throw std::runtime_error(SDL_GetError());
}

sgf::type::window_size window::init_size() const noexcept
{
    return {p_info.size.w, p_info.size.h};
}

sgf::type::window_size window::current_size() const
{
    std::int32_t w, h;
    if (!SDL_GetWindowSize(p_impl->window, &w, &h))
        throw std::runtime_error(SDL_GetError());

    return {static_cast<std::uint32_t>(w), static_cast<std::uint32_t>(h)};
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

void window::on_resize(std::function<void()> f)
{
    p_on_resize = f;
}