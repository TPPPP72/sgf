#ifndef SGF_SCENE_MANAGER_HPP
#define SGF_SCENE_MANAGER_HPP

#include <sgf/base/renderer.hpp>
#include <sgf/scene/scene.hpp>

namespace sgf
{

class scene_manager
{
public:
    void push_scene(std::unique_ptr<scene> new_scene)
    {
        if (new_scene)
        {
            new_scene->on_init();
            m_scenes.push_back(std::move(new_scene));
        }
    }

    void pop_scene()
    {
        if (!m_scenes.empty())
            m_scenes.pop_back();
    }

    void change_scene(std::unique_ptr<scene> new_scene)
    {
        m_scenes.clear();
        push_scene(std::move(new_scene));
    }

    void input(const input_event &e)
    {
        for (auto &s : m_scenes)
        {
            if (s->should_update)
                s->on_input(e);
        }
    }

    void update(const frame_context &ctx)
    {
        for (auto &s : m_scenes)
        {
            if (s->should_update)
                s->on_update(ctx);
        }
    }

    void render(base::renderer &renderer)
    {
        for (auto &s : m_scenes)
        {
            if (s->should_render)
                s->on_render(renderer);
        }
    }

    scene *get_current() const
    {
        if (m_scenes.empty())
            return nullptr;

        return m_scenes.back().get();
    }

    bool empty() const
    {
        return m_scenes.empty();
    }

private:
    std::vector<std::unique_ptr<scene>> m_scenes;
};

} // namespace sgf

#endif