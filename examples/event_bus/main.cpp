#include "game_scene.hpp"
#include <sgf/kernel.hpp>
#include <sgf/scene/scene_manager.hpp>
#include <string>

class event_bus : public sgf::kernel<event_bus>
{
public:
    event_bus() : kernel("event_bus", {800, 600}, {800, 600}, 0)
    {
        auto game = std::make_unique<game_scene>(1);

        m_manager.change_scene(std::move(game));
    }

    void on_input(kernel<event_bus> &k, const sgf::input_event &e)
    {
        m_manager.input(e);
    }

    void on_update(kernel<event_bus> &k, const sgf::frame_context &ctx)
    {
        k.get_window().set_title("event_bus | FPS : " + std::to_string(k.get_current_fps()));
        m_manager.update(ctx);
    }

    void on_render(kernel<event_bus> &k)
    {
        auto &rd = k.get_renderer();
        m_manager.render(rd);
    }

private:
    sgf::scene_manager m_manager;
};

int main()
{
    event_bus{}.run();
}