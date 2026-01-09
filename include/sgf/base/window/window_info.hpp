#ifndef SGF_BASE_WINDOW_INFO_HPP
#define SGF_BASE_WINDOW_INFO_HPP

#include <cstdint>
#include <string>

namespace sgf::base
{

struct window_info
{
    std::string title;
    std::uint32_t width;
    std::uint32_t height;
};

} // namespace sgf::base

#endif