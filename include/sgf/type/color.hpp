#ifndef SGF_TYPE_COLOR_HPP
#define SGF_TYPE_COLOR_HPP

#include <cstdint>

namespace sgf::type
{

struct color
{
    std::uint8_t r{0};
    std::uint8_t g{0};
    std::uint8_t b{0};
    std::uint8_t a{0};

    static const color red;
    static const color green;
    static const color blue;
    static const color white;
    static const color black;
};

inline constexpr color color::red{255, 0, 0, 255};
inline constexpr color color::green{0, 255, 0, 255};
inline constexpr color color::blue{0, 0, 255, 255};
inline constexpr color color::white{255, 255, 255, 255};
inline constexpr color color::black{0, 0, 0, 255};

} // namespace sgf::type

#endif