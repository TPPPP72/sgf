#ifndef SGF_BASE_WINDOW_HPP
#define SGF_BASE_WINDOW_HPP

#include <functional>
#include <memory>
#include <sgf/base/guard/video_system.hpp>
#include <sgf/base/window/window_event.hpp>
#include <sgf/base/window/window_info.hpp>

namespace sgf::base
{

class window
{
public:
    explicit window(const window_info &);
    ~window();
    window_info init_info() const noexcept;
    window_info current_info() const;
    void poll_events();
    std::vector<window_event> events() const noexcept;
    window_event current_event() const noexcept;
    void *get() const noexcept;
    type::window_size init_size() const noexcept;
    type::window_size current_size() const;
    std::string init_title() const noexcept;
    std::string current_title() const noexcept;
    void set_title(const std::string &title);
    void set_fullscreen(bool is_enable);
    bool is_fullscreen() const noexcept;
    void on_exit(std::function<void()>);
    void on_resize(std::function<void()>);

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
    window_info p_info;
    window_event p_current_event;
    std::vector<window_event> p_events;
    bool p_is_fullscreen{false};
    std::function<void()> p_on_exit{nullptr};
    std::function<void()> p_on_resize{nullptr};
    guard::video_system guard;
};

} // namespace sgf::base

#endif