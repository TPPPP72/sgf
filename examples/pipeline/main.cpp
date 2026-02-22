#include "test_scene.hpp"
#include <memory>
#include <sgf/kernel.hpp>
#include <sgf/scene/scene_manager.hpp>
#include <string>

class pipeline : public sgf::kernel<pipeline>
{
public:
    pipeline()
        : kernel("pipeline", {500, 500}, {500, 500}, 0)
    {
        auto test = std::make_unique<test_scene>(1);

        m_manager.change_scene(std::move(test));
    }

    void on_input(kernel<pipeline> &k, const sgf::input_event &e) {}

    void on_update(kernel<pipeline> &k, const sgf::frame_context &ctx)
    {
        k.get_window().set_title("pipeline | FPS : " + std::to_string(k.get_current_fps()));
        m_manager.update(ctx);
    }

    void on_render(kernel<pipeline> &k)
    {
        auto &rd = k.get_renderer();
        m_manager.render(rd);
    }

private:
    sgf::scene_manager m_manager;
};

int main()
{
    pipeline{}.run();
}