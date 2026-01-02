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
};

inline constexpr color red{255, 0, 0, 255};
inline constexpr color green{0, 255, 0, 255};
inline constexpr color blue{0, 0, 255, 255};
inline constexpr color white{255, 255, 255, 255};
inline constexpr color black{0, 0, 0, 255};

} // namespace sgf::type

#endif