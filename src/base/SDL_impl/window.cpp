#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <sgf/base/window/window.hpp>
#include <stdexcept>

using namespace sgf::base;

struct window::impl
{
    SDL_Window *window = nullptr;
};

window::window(const window_info &inf) : p_impl(std::make_unique<impl>())
{
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

window_event window::current_event() const
{
    return p_event;
}

void window::poll_event()
{
    p_event.events.fill(false);
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

        case SDL_EVENT_WINDOW_RESIZED:
        case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
            if (p_on_resize != nullptr)
                p_on_resize();
            break;

        case SDL_EVENT_KEY_DOWN:
            p_event.events[static_cast<std::size_t>(event_type::key_down)] = true;
            p_event.keys[static_cast<std::size_t>(event.key.scancode)]     = true;
            break;

        case SDL_EVENT_KEY_UP:
            p_event.events[static_cast<std::size_t>(event_type::key_up)] = true;
            p_event.keys[static_cast<std::size_t>(event.key.scancode)]   = false;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            p_event.events[static_cast<std::size_t>(event_type::mouse_button_down)] = true;
            p_event.buttons[static_cast<std::size_t>(event.button.button)]          = true;
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            p_event.events[static_cast<std::size_t>(event_type::mouse_button_up)] = true;
            p_event.buttons[static_cast<std::size_t>(event.button.button)]        = false;
            break;

        case SDL_EVENT_MOUSE_MOTION:
            p_event.pos.x = static_cast<double>(event.motion.x);
            p_event.pos.y = static_cast<double>(event.motion.y);
            break;
        }
    }
    ++p_poll_event_count;
}

void *window::get() const noexcept
{
    return p_impl->window;
}

sgf::type::window_size window::init_size() const noexcept
{
    return {p_info.width, p_info.height};
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

std::uint32_t window::poll_event_count() const noexcept
{
    return p_poll_event_count;
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