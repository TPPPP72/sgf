#ifndef SGF_KERNEL_HPP
#define SGF_KERNEL_HPP

#include <chrono>
#include <sgf/base/input_system.hpp>
#include <sgf/base/renderer.hpp>
#include <sgf/context/frame_context.hpp>
#include <thread>

namespace sgf
{

template <typename game>
class kernel
{
public:
    // Create window with no VSync
    kernel(const std::string &title, const type::view_size &init_vs, const type::window_size &init_ws, type::uint32 max_fps) : p_view_size(init_vs), p_max_fps(max_fps), p_window({title, init_ws}), p_renderer(p_window), p_viewport(p_window, init_vs)
    {
        init();
    }
    // Create window with VSync
    kernel(const std::string &title, const type::view_size &init_vs, const type::world_size &init_ws) : kernel(title, init_vs, init_ws, 0) {}
    base::window &get_window() noexcept
    {
        return p_window;
    }
    base::renderer &get_renderer() noexcept
    {
        return p_renderer;
    }
    type::uint32 get_current_fps() const noexcept
    {
        return p_current_fps;
    }
    // Launch game
    void run()
    {
        using clock = std::chrono::steady_clock;
        using ns    = std::chrono::nanoseconds;

        constexpr ns max_dt{50'000'000};

        auto last_time     = clock::now();
        auto fps_last_time = clock::now();
        type::uint32 frame_count{0};

        while (!p_exit)
        {
            auto now      = clock::now();
            ns frame_time = std::chrono::duration_cast<ns>(now - last_time);
            last_time     = now;

            ns dt = std::min(frame_time, max_dt);

            input();

            update(dt);

            render();

            if (p_max_fps > 0)
            {
                ns target_frame{1'000'000'000 / p_max_fps};
                auto loop_now = clock::now();
                while (std::chrono::duration_cast<ns>(loop_now - now) < target_frame)
                {
                    ns remaining = target_frame - std::chrono::duration_cast<ns>(loop_now - now);
                    if (remaining > std::chrono::milliseconds(2))
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    else
                        std::this_thread::yield();
                    loop_now = clock::now();
                }
            }

            ++frame_count;
            auto current_loop_end = clock::now();
            auto duration         = std::chrono::duration_cast<std::chrono::milliseconds>(current_loop_end - fps_last_time);

            if (duration.count() >= 500)
            {
                p_current_fps = static_cast<type::uint32>(frame_count * 1000.0 / duration.count());
                frame_count   = 0;
                fps_last_time = current_loop_end;
            }
        }
    }

private:
    void init()
    {
        if (p_max_fps == 0)
            p_renderer.set_vsync(true);
        else
            p_renderer.set_vsync(false);

        p_renderer.set_draw_blend(true);

        p_input_system.bind_window(&p_window);
        p_input_system.bind_viewport(&p_viewport);

        p_window.on_exit([this]()
                         {
                             p_exit = true;
                         });
        p_window.on_resize([this]()
                           {
                               p_viewport.update();
                           });
    }
    void input()
    {
        p_window.poll_events();
        p_input_system.dispatch([this](const input_event &event)
                                {
                                    static_cast<game *>(this)->on_input(*this, event);
                                });
    }
    void update(std::chrono::nanoseconds dt)
    {
        static_cast<game *>(this)->on_update(*this, frame_context{dt, p_input_system.get_mouse_view_position()});
    }
    void render()
    {
        p_renderer.begin_frame(p_viewport);
        p_renderer.clear();
        static_cast<game *>(this)->on_render(*this);
        p_renderer.present();
        p_renderer.end_frame();
    }

private:
    type::view_size p_view_size{0, 0};
    type::uint32 p_max_fps{0};
    type::uint32 p_current_fps{0};
    base::window p_window;
    base::renderer p_renderer;
    base::viewport p_viewport;
    base::input_system p_input_system;
    bool p_exit{false};
};

} // namespace sgf

#endif