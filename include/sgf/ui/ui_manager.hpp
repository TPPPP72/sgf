#ifndef SGF_UI_MANAGER_HPP
#define SGF_UI_MANAGER_HPP

#include <memory>
#include <sgf/context/frame_context.hpp>
#include <sgf/event/input_event.hpp>
#include <sgf/ui/view.hpp>
#include <vector>

namespace sgf
{

class render_pipeline;

class ui_manager
{

public:
    bool dispatch(const input_event &e)
    {
        if (m_views.empty())
            return false;

        // 若有捕获视图，如拖拽等事件，捕获周期由视图自身决定
        if (e.is_mouse_event())
        {
            if (auto captured = m_captured_view.lock())
                return captured->on_input(e);
        }

        ensure_sorted();

        if (e.is_mouse_event())
        {
            for (auto it = m_views.rbegin(); it != m_views.rend(); ++it)
            {
                auto &view = *it;
                if (!view->is_active())
                    continue;

                if (view->is_inside(e.pos))
                {
                    if (e.type == base::event_type::mouse_button_up)
                        set_focus(view);

                    return view->on_input(e);
                }
            }
        }
        else if (e.is_key_event())
        {
            if (auto focus = m_focused_view.lock())
                return focus->on_input(e);
        }

        return false;
    }

    void update(const frame_context &ctx)
    {
        std::shared_ptr<view> current_hover = nullptr;

        if (auto captured = m_captured_view.lock())
        {
            current_hover = captured;
        }
        else
        {
            auto mouse_pos = ctx.mouse_view_pos;
            for (auto it = m_views.rbegin(); it != m_views.rend(); ++it)
            {
                if ((*it)->is_active() && (*it)->is_inside(mouse_pos))
                {
                    current_hover = *it;
                    break;
                }
            }
        }

        auto last_hover = m_hovered_view.lock();
        if (current_hover != last_hover)
        {
            if (last_hover)
                last_hover->on_mouse_leave();
            if (current_hover)
                current_hover->on_mouse_enter();
            m_hovered_view = current_hover;
        }

        for (auto &v : m_views)
        {
            if (v->is_active())
                v->on_update(ctx);
        }
    }

    void render(render_pipeline &p)
    {
        for (auto &v : m_views)
        {
            if (v->m_is_visible)
                v->on_render(p);
        }
    }

    void set_focus(std::shared_ptr<view> target)
    {
        auto old_focus = m_focused_view.lock();
        if (old_focus == target)
            return;

        if (old_focus)
            old_focus->on_focus_changed(false);

        m_focused_view = target;
        if (target)
            target->on_focus_changed(true);
    }

    void add_view(std::shared_ptr<view> v)
    {
        v->p_manager = this;
        m_views.push_back(v);
        m_needs_sort = true;
    }

    void capture_mouse(std::shared_ptr<view> target)
    {
        m_captured_view = target;
    }

    void release_mouse()
    {
        m_captured_view.reset();
    }

private:
    void ensure_sorted()
    {
        if (m_needs_sort)
        {
            std::stable_sort(m_views.begin(), m_views.end(),
                             [](const auto &a, const auto &b)
                             {
                                 return a->z_index < b->z_index;
                             });
            m_needs_sort = false;
        }
    }

    std::vector<std::shared_ptr<view>> m_views;
    std::weak_ptr<view> m_focused_view;
    std::weak_ptr<view> m_captured_view;
    std::weak_ptr<view> m_hovered_view;
    bool m_needs_sort{true};
};

} // namespace sgf

#endif