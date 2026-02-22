#ifndef SGF_UTIL_COLOR_UTIL_HPP
#define SGF_UTIL_COLOR_UTIL_HPP

#include <sgf/random/random.hpp>
#include <sgf/type/color.hpp>

namespace sgf::util
{

/**
 * @brief 生成随机颜色
 * @tparam ColorT 颜色类型，如 sgf::type::color 或 sgf::type::colorf
 */
template <typename ColorT>
inline ColorT make_random_color(bool random_alpha = false)
{
    using T = decltype(ColorT::r);

    T max_val = type::color_limits<T>::max();
    T min_val = type::color_limits<T>::min();

    return ColorT{
        random::range<T>(min_val, max_val),
        random::range<T>(min_val, max_val),
        random::range<T>(min_val, max_val),
        random_alpha ? random::range<T>(min_val, max_val) : max_val};
}

} // namespace sgf::util

#endif