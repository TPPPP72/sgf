#ifndef SGF_BASE_INPUT_SYSTEM_HPP
#define SGF_BASE_INPUT_SYSTEM_HPP

#include <sgf/base/viewport.hpp>
#include <sgf/base/window/window.hpp>
#include <sgf/event/input_event.hpp>
#include <sgf/logger/logger.hpp>
#include <sgf/type/position.hpp>

namespace sgf::base
{

class input_system
{
public:
    input_system()                                = default;
    ~input_system()                               = default;
    input_system(const input_system &)            = delete;
    input_system &operator=(const input_system &) = delete;

    void bind_window(base::window *w) noexcept
    {
        win = w;
    }

    void bind_viewport(base::viewport *v) noexcept
    {
        vp = v;
    }

    template <typename F, typename = std::enable_if_t<std::is_invocable_v<F, input_event>>>
    void dispatch(F &&callback) const
    {
        if (win == nullptr)
            SGF_ERROR("Can not use dispatch before bind window");
        if (vp == nullptr)
            SGF_ERROR("Can not use dispatch before bind viewport");
        for (auto &&e : win->events())
        {
            callback({e.type, e.key, e.mouse, vp->to_view_position(e.pos)});
        }
    }

    type::window_position get_mouse_window_position() const
    {
        if (win == nullptr)
            SGF_ERROR("Can not use get_mouse_window_position before bind window");
        return win->current_event().pos;
    }

    type::view_position get_mouse_view_position() const
    {
        if (win == nullptr)
            SGF_ERROR("Can not use get_mouse_view_position before bind window");
        if (vp == nullptr)
            SGF_ERROR("Can not use get_mouse_view_position before bind viewport");
        return vp->to_view_position(win->current_event().pos);
    }

private:
    base::window *win{nullptr};
    base::viewport *vp{nullptr};
};

} // namespace sgf::base

#endif