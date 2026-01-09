#pragma once

#include <string>

inline std::string get_default_font() noexcept
{
#ifdef _WIN32
    return "C:/Windows/Fonts/msyh.ttc";
#elif defined(__APPLE__)
    return "/System/Library/Fonts/PingFang.ttc";
#else
    return "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
#endif
}