#include "game_scene.hpp"
#include <memory>
#include <sgf/kernel.hpp>
#include <sgf/scene/scene_manager.hpp>
#include <string>

class cameral : public sgf::kernel<cameral>
{
public:
    cameral()
        : kernel("cameral", {800, 600}, {800, 600}, 0)
    {
        auto game = std::make_unique<game_scene>(1);

        m_manager.change_scene(std::move(game));
    }

    void on_input(kernel<cameral> &k, const sgf::input_event &e)
    {
    }

    void on_update(kernel<cameral> &k, const sgf::frame_context &ctx)
    {
        k.get_window().set_title("cameral | FPS : " + std::to_string(k.get_current_fps()));
        m_manager.update(ctx);
    }

    void on_render(kernel<cameral> &k)
    {
        auto &rd = k.get_renderer();
        m_manager.render(rd);
    }

private:
    sgf::scene_manager m_manager;
};

int main()
{
    cameral{}.run();
}