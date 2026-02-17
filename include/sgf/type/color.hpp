#ifndef SGF_TYPE_COLOR_HPP
#define SGF_TYPE_COLOR_HPP

#include <cstdint>
#include <limits>
#include <type_traits>

namespace sgf::type
{

template <typename T>
struct color_limits
{
    static constexpr T max()
    {
        if constexpr (std::is_floating_point_v<T>)
            return static_cast<T>(1.0);
        else
            return std::numeric_limits<T>::max();
    }

    static constexpr T min()
    {
        return static_cast<T>(0);
    }
};

template <typename T>
struct color_t
{
    constexpr color_t() = default;
    constexpr color_t(T r, T g, T b, T a)
        : r(r), g(g), b(b), a(a) {}

    T r{0};
    T g{0};
    T b{0};
    T a{0};

    static const color_t black;
    static const color_t white;
    static const color_t red;
    static const color_t green;
    static const color_t blue;

    template <typename U>
    constexpr color_t(const color_t<U> &other)
        : r(convert_v<U, T>(other.r)),
          g(convert_v<U, T>(other.g)),
          b(convert_v<U, T>(other.b)),
          a(convert_v<U, T>(other.a)) {}

private:
    template <typename From, typename To>
    static constexpr To convert_v(From val)
    {
        if constexpr (std::is_same_v<From, To>)
            return val;
        if constexpr (std::is_floating_point_v<To> && std::is_integral_v<From>)
            return static_cast<To>(val) / static_cast<To>(255);
        if constexpr (std::is_integral_v<To> && std::is_floating_point_v<From>)
            return static_cast<To>(val * 255);
        return static_cast<To>(val);
    }
};

template <typename T>
inline constexpr color_t<T> color_t<T>::black{0, 0, 0, color_limits<T>::max()};

template <typename T>
inline constexpr color_t<T> color_t<T>::white{color_limits<T>::max(), color_limits<T>::max(), color_limits<T>::max(), color_limits<T>::max()};

template <typename T>
inline constexpr color_t<T> color_t<T>::red{color_limits<T>::max(), 0, 0, color_limits<T>::max()};

template <typename T>
inline constexpr color_t<T> color_t<T>::green{0, color_limits<T>::max(), 0, color_limits<T>::max()};

template <typename T>
inline constexpr color_t<T> color_t<T>::blue{0, 0, color_limits<T>::max(), color_limits<T>::max()};

using color  = color_t<std::uint8_t>;
using colorf = color_t<float>;

} // namespace sgf::type

#endif