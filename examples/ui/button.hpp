#include <functional>
#include <sgf/render_pipeline/render_pipeline.hpp>
#include <sgf/type/color.hpp>
#include <sgf/ui/ui_manager.hpp>
#include <sgf/ui/view.hpp>

class button : public sgf::view
{
public:
    sgf::type::color normal_color = sgf::type::color::white;
    sgf::type::color hover_color  = sgf::type::color::red;
    std::function<void()> on_click;

    void on_mouse_enter() override { m_background_color = hover_color; }
    void on_mouse_leave() override { m_background_color = normal_color; }

    bool on_input(const sgf::input_event &e) override
    {
        if (e.type == sgf::base::event_type::mouse_button_down)
            return true;
        if (e.type == sgf::base::event_type::mouse_button_up)
        {
            m_background_color = hover_color;
            if (on_click)
                on_click();
            return true;
        }
        return false;
    }

    void on_render(sgf::render_pipeline &p) override
    {
        p.submit(view_rect(), m_background_color, sgf::graphic_style::fill, 0, z_index);
    }

private:
    sgf::type::color m_background_color = normal_color;
};