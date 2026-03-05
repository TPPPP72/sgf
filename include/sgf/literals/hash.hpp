#ifndef SGF_LITERALS_HASH_HPP
#define SGF_LITERALS_HASH_HPP

#include <sgf/util/hash.hpp>

namespace sgf::literals
{

constexpr std::uint32_t operator""_hash(const char *str, std::size_t len)
{
    return sgf::util::hash(std::string_view(str, len));
}

} // namespace sgf::literals

#endif