#ifndef SGF_BASE_GUARD_FONT_SYSTEM_HPP
#define SGF_BASE_GUARD_FONT_SYSTEM_HPP

namespace sgf::base::guard
{
class font_system
{
public:
    font_system();
    ~font_system();
    font_system(const font_system &)            = delete;
    font_system &operator=(const font_system &) = delete;
    font_system(font_system &&)                 = delete;
    font_system &operator=(font_system &&)      = delete;
};
}; // namespace sgf::base::guard

#endif