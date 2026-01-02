#ifndef SDL3_UTILS_CONVERT_HPP
#define SDL3_UTILS_CONVERT_HPP

#include "../../../../include/sgf/type/color.hpp"
#include "../../../../include/sgf/type/rect.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>

namespace sgf::base
{

static inline SDL_FRect to_frect(const sgf::type::rect &r)
{
    return {static_cast<float>(r.x),
            static_cast<float>(r.y),
            static_cast<float>(r.w),
            static_cast<float>(r.h)};
}

static inline SDL_Color to_color(const sgf::type::color &c)
{
    return {c.r,
            c.g,
            c.b,
            c.a};
}

} // namespace sgf::base

#endif