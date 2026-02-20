#ifndef SGF_LOGGER_HPP
#define SGF_LOGGER_HPP

#include <cstdarg>
#include <cstdio>
#include <string>

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef _WIN32
#include <windows.h>
#endif

namespace sgf
{

enum class log_level
{
    info,
    warn,
    error
};

class logger
{
public:
    static void log(log_level level, const char *fmt, ...)
    {
        char buffer[1024];
        va_list args;
        va_start(args, fmt);
        std::vsnprintf(buffer, sizeof(buffer), fmt, args);
        va_end(args);

        const char *color_code = "";
        const char *reset_code = "\033[0m";
        const char *prefix     = "";

        switch (level)
        {
        case log_level::info:
            color_code = "\033[32m";
            prefix     = "[INFO] ";
            break;
        case log_level::warn:
            color_code = "\033[33m";
            prefix     = "[WARN] ";
            break;
        case log_level::error:
            color_code = "\033[31m";
            prefix     = "[ERROR] ";
            break;
        }

        std::string final_msg = std::string(color_code) + prefix + buffer + reset_code + "\n";

        std::printf("%s", final_msg.c_str());

#ifdef _WIN32
        OutputDebugStringA(final_msg.c_str());
#endif
    }
};

#define SGF_INFO(fmt, ...) sgf::logger::log(sgf::log_level::info, fmt, ##__VA_ARGS__)
#define SGF_WARN(fmt, ...) sgf::logger::log(sgf::log_level::warn, fmt, ##__VA_ARGS__)
#define SGF_ERROR(fmt, ...) sgf::logger::log(sgf::log_level::error, fmt, ##__VA_ARGS__)

} // namespace sgf

#endif