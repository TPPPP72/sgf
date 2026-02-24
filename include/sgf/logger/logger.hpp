#ifndef SGF_LOGGER_HPP
#define SGF_LOGGER_HPP

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
    static void log(log_level level, const char *fmt, ...);
};

#define SGF_INFO(fmt, ...) sgf::logger::log(sgf::log_level::info, fmt, ##__VA_ARGS__)
#define SGF_WARN(fmt, ...) sgf::logger::log(sgf::log_level::warn, fmt, ##__VA_ARGS__)
#define SGF_ERROR(fmt, ...) sgf::logger::log(sgf::log_level::error, fmt, ##__VA_ARGS__)

} // namespace sgf

#endif