#ifndef SGF_KERNEL_HPP
#define SGF_KERNEL_HPP

#include "base/renderer.hpp"
#include "base/viewport.hpp"
#include "base/window/window.hpp"
#include "sgf/input_system.hpp"
#include "type/size.hpp"
#include <chrono>
#include <cstdint>
#include <thread>

namespace sgf
{

template <typename game>
class kernel
{
public:
    // Create window with no VSync
    kernel(const std::string &title, const type::world_size &ws, std::uint32_t max_fps) : p_ws(ws), p_max_fps(max_fps), p_window({title, ws.w, ws.h}), p_renderer(p_window), p_viewport(p_window)
    {
        init();
    }
    // Create window with VSync
    kernel(const std::string &title, const type::world_size &ws) : kernel(title, ws, 0) {}
    base::window &get_window() noexcept
    {
        return p_window;
    }
    base::renderer &get_renderer() noexcept
    {
        return p_renderer;
    }
    std::uint32_t get_current_fps() const noexcept
    {
        return p_current_fps;
    }
    // Launch game
    void run()
    {
        using clock = std::chrono::steady_clock;
        using ns    = std::chrono::nanoseconds;

        constexpr ns logic_step{16'666'666}; // 游戏逻辑使用固定 60 fps
        constexpr ns max_frame_time{250'000'000};
        constexpr int max_updates_per_frame = 5;

        ns accumulator{0};
        auto last_time = clock::now();

        auto fps_last_time = clock::now();
        std::uint32_t frame_count{0};

        while (true)
        {
            auto now      = clock::now();
            ns frame_time = std::chrono::duration_cast<ns>(now - last_time);
            last_time     = now;

            frame_time = std::min(frame_time, max_frame_time);
            accumulator += frame_time;

            control();

            std::int32_t updates = 0;
            while (accumulator >= logic_step && updates < max_updates_per_frame)
            {
                update(logic_step);
                accumulator -= logic_step;
                ++updates;
            }

            if (updates == max_updates_per_frame)
                accumulator = ns{0};

            render();

            ++frame_count;
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - fps_last_time);

            if (duration.count() >= 500)
            {
                p_current_fps = static_cast<double>(frame_count) / (duration.count() / 1000.0);
                frame_count   = 0;
                fps_last_time = now;
            }

            if (p_max_fps > 0)
            {
                ns target_frame{1'000'000'000 / p_max_fps};

                auto frame_end = clock::now();
                ns used        = std::chrono::duration_cast<ns>(frame_end - now);

                if (used < target_frame)
                    std::this_thread::sleep_for(target_frame - used);
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

        input_system::instance().bind(&p_window);
        p_window.on_resize([this]()
                           {
                               p_viewport.update();
                           });
    }
    void control()
    {
        p_window.poll_event();
        input_system::instance().update();
    }
    void update(std::chrono::nanoseconds dt)
    {
        static_cast<game *>(this)->on_update(*this, dt);
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
    type::world_size p_ws{0, 0};
    std::uint32_t p_max_fps{0};
    std::uint32_t p_current_fps{0};
    base::window p_window;
    base::renderer p_renderer;
    base::viewport p_viewport;
};

} // namespace sgf

#endif