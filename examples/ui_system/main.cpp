#include "game_scene.hpp"

class ui : public sgf::kernel<ui>
{
public:
    ui() : kernel("ui_system", {800, 600}, {800, 600}, 0)
    {
        auto game = std::make_unique<game_scene>(1);

        m_manager.change_scene(std::move(game));
    }

    void on_input(kernel<ui> &k, const sgf::input_event &e)
    {
        m_manager.input(e);
    }

    void on_update(kernel<ui> &k, const sgf::frame_context &ctx)
    {
        k.get_window().set_title("ui | FPS : " + std::to_string(k.get_current_fps()));
        m_manager.update(ctx);
    }

    void on_render(kernel<ui> &k)
    {
        auto &rd = k.get_renderer();
        m_manager.render(rd);
    }

private:
    sgf::scene_manager m_manager;
};

int main()
{
    ui{}.run();
}