#include "game_scene.hpp"
#include "pause_scene.hpp"
#include "splash_scene.hpp"
#include <memory>
#include <sgf/kernel.hpp>
#include <sgf/scene/scene_manager.hpp>
#include <string>

class scene_switch : public sgf::kernel<scene_switch>
{
public:
    scene_switch()
        : kernel("scene switch", {500, 500}, {500, 500}, 0)
    {
        auto splash = std::make_unique<splash_scene>(1, [this]()
                                                     {
                                                         m_manager.change_scene(std::make_unique<game_scene>(3));
                                                     });

        m_manager.change_scene(std::move(splash));
    }

    void on_input(kernel<scene_switch> &k, const sgf::input_event &e)
    {
        if (e.type == sgf::base::event_type::key_down && e.key == sgf::base::key_code::p)
        {
            auto current = m_manager.get_current();
            if (current && current->id() != 2)
                m_manager.push_scene(std::make_unique<pause_scene>(2, current));
        }
        if (e.type == sgf::base::event_type::key_down && e.key == sgf::base::key_code::space)
        {
            if (m_manager.get_current()->id() == 2)
                m_manager.pop_scene();
        }
    }

    void on_update(kernel<scene_switch> &k, const sgf::frame_context &ctx)
    {
        k.get_window().set_title("scene_switch | FPS : " + std::to_string(k.get_current_fps()));
        m_manager.update(ctx);
    }

    void on_render(kernel<scene_switch> &k)
    {
        auto &rd = k.get_renderer();
        m_manager.render(rd);
    }

private:
    sgf::scene_manager m_manager;
};

int main()
{
    scene_switch{}.run();
}