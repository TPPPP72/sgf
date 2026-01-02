#ifndef SGF_BASE_SURFACE_HPP
#define SGF_BASE_SURFACE_HPP

#include "../type/color.hpp"
#include "font.hpp"
#include <memory>
#include <string>

namespace sgf::base
{

class surface
{
public:
    explicit surface(const font &, const std::string &text, const sgf::type::color &);
    ~surface();
    void *get() const noexcept;

private:
    struct impl;
    std::unique_ptr<impl> p_impl;
};

} // namespace sgf::base

#endif