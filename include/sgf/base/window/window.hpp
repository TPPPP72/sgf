#ifndef SGF_BASE_WINDOW_HPP
#define SGF_BASE_WINDOW_HPP

#include "../../type/size.hpp"
#include "../guard/video_system.hpp"
#include "window_event.hpp"
#include "window_info.hpp"
#include <cstdint>
#include <functional>
#include <memory>

namespace sgf::base
{

class window
{
public:
    explicit window(const window_info &);
    ~window();
    window_info init_info() const noexcept;
    window_info current_info() const;
    window_event current_event() const;
    void poll_event();
    void *get() const noexcept;
    type::window_size init_size() const noexcept;
    type::window_size current_size() const;
    void set_fullscreen(bool is_enable);
    bool is_fullscreen() const noexcept;
    std::uint32_t poll_event_count() const noexcept;
    void on_exit(std::function<void()>);
    void on_resize(std::function<void()>);

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
    window_info p_info;
    window_event p_event;
    bool p_is_fullscreen{false};
    std::uint32_t p_poll_event_count{0};
    std::function<void()> p_on_exit{nullptr};
    std::function<void()> p_on_resize{nullptr};
    guard::video_system guard;
};

} // namespace sgf::base

#endif