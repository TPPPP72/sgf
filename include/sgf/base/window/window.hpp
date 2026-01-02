#ifndef SGF_BASE_WINDOW_HPP
#define SGF_BASE_WINDOW_HPP

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
    window_info                              init_info() const noexcept;
    window_info                              current_info() const;
    void                                     poll_event();
    void                                    *get() const noexcept;
    std::tuple<std::uint32_t, std::uint32_t> init_size() const noexcept;
    std::tuple<std::uint32_t, std::uint32_t> current_size() const;
    void                                     set_fullscreen(bool is_enable);
    bool                                     is_fullscreen() const noexcept;
    void                                     on_exit(std::function<void()>);

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
    window_info           p_info;
    bool                  p_is_fullscreen{false};
    std::function<void()> p_on_exit{nullptr};
};

} // namespace sgf::base

#endif