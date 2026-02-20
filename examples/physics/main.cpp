#include "game_scene.hpp"
#include <sgf/kernel.hpp>
#include <sgf/scene/scene_manager.hpp>
#include <string>

class physics : public sgf::kernel<physics>
{
public:
    physics() : kernel("physics", {800, 600}, {800, 600}, 0)
    {
        auto game = std::make_unique<game_scene>(1);

        m_manager.change_scene(std::move(game));
    }

    void on_update(kernel<physics> &k, std::chrono::nanoseconds dt)
    {
        k.get_window().set_title("physics | FPS : " + std::to_string(k.get_current_fps()));
        m_manager.update(dt);
    }

    void on_render(kernel<physics> &k)
    {
        auto &rd = k.get_renderer();
        m_manager.render(rd);
    }

private:
    sgf::scene_manager m_manager;
};

int main()
{
    physics{}.run();
}