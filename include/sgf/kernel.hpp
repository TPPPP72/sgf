#ifndef SGF_KERNEL_HPP
#define SGF_KERNEL_HPP

#include "base/renderer.hpp"
#include "base/window/window.hpp"
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
    kernel(const std::string &title, const type::world_size &ws, std::uint32_t max_fps) : p_ws(ws), p_window({title, ws.w, ws.h}), p_renderer(p_window)
    {
        if (max_fps == 0)
            p_renderer.set_vsync(true);
        else
            p_renderer.set_vsync(false);
    }
    // Create window with VSync
    kernel(const std::string &title, const type::world_size &ws) : kernel(title, ws, 0) {}
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

        bool running = true;

        while (running)
        {
            auto now      = clock::now();
            ns frame_time = std::chrono::duration_cast<ns>(now - last_time);
            last_time     = now;

            frame_time = std::min(frame_time, max_frame_time);
            accumulator += frame_time;

            running = control();

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
    void control() {}
    void update(std::chrono::nanoseconds dt) {}
    void render() {}

private:
    type::world_size p_ws{0, 0};
    std::uint32_t p_max_fps{0};
    base::window p_window;
    base::renderer p_renderer;
};

} // namespace sgf

#endif