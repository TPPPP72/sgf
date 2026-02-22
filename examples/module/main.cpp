#include "game_scene.hpp"
#include "sgf/context/frame_context.hpp"
#include "sgf/event/input_event.hpp"
#include <memory>
#include <sgf/kernel.hpp>
#include <sgf/scene/scene_manager.hpp>
#include <string>

class module : public sgf::kernel<module>
{
public:
    module() :kernel("module", {300, 300}, {800, 600}, 0)
    {
        auto game = std::make_unique<game_scene>(1);

        m_manager.change_scene(std::move(game));
    }

    void on_input(kernel<module> &k, const sgf::input_event &e)
    {
        m_manager.input(e);
    }

    void on_update(kernel<module> &k, const sgf::frame_context &ctx)
    {
        k.get_window().set_title("module | FPS : " + std::to_string(k.get_current_fps()));
        m_manager.update(ctx);
    }

    void on_render(kernel<module> &k)
    {
        auto &rd = k.get_renderer();
        m_manager.render(rd);
    }

private:
    sgf::scene_manager m_manager;
};

int main()
{
    module{}.run();
}