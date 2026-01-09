#ifndef SGF_BASE_TEXTURE_HPP
#define SGF_BASE_TEXTURE_HPP

#include "../type/size.hpp"
#include "renderer.hpp"
#include "surface.hpp"
#include <filesystem>

namespace sgf::base
{

class texture
{
public:
    explicit texture(const renderer &, std::uint32_t width, std::uint32_t height);
    explicit texture(const renderer &, const std::filesystem::path &);
    explicit texture(const renderer &, const surface &);
    explicit texture(const renderer &, const font &, const std::string &text, const sgf::type::color &);
    ~texture();
    void *get() const noexcept;
    type::resource_size size() const;

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
};

} // namespace sgf::base

#endif