#ifndef SGF_BASE_WINDOW_INFO_HPP
#define SGF_BASE_WINDOW_INFO_HPP

#include "../../type/size.hpp"
#include <string>

namespace sgf::base
{

struct window_info
{
    std::string title;
    type::window_size size;
};

} // namespace sgf::base

#endif