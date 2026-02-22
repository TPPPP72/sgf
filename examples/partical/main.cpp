#include "game_scene.hpp"
#include <sgf/kernel.hpp>
#include <sgf/scene/scene_manager.hpp>
#include <string>

class partical : public sgf::kernel<partical>
{
public:
    partical() : kernel("partical", {800, 600}, {800, 600}, 0)
    {
        auto game = std::make_unique<game_scene>(1);

        m_manager.change_scene(std::move(game));
    }

    void on_update(kernel<partical> &k, std::chrono::nanoseconds dt)
    {
        k.get_window().set_title("partical | FPS : " + std::to_string(k.get_current_fps()));
        m_manager.update(dt);
    }

    void on_render(kernel<partical> &k)
    {
        auto &rd = k.get_renderer();
        m_manager.render(rd);
    }

private:
    sgf::scene_manager m_manager;
};

int main()
{
    partical{}.run();
}