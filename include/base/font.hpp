#ifndef SGF_BASE_FONT_HPP
#define SGF_BASE_FONT_HPP

#include <cstdint>
#include <filesystem>
#include <memory>

namespace sgf::base
{

class font
{
public:
    explicit font(const std::filesystem::path &, std::uint32_t size);
    ~font();
    void *get() const noexcept;

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
};

} // namespace sgf::base

#endif