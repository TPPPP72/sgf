#ifndef SGF_UTIL_HASH_HPP
#define SGF_UTIL_HASH_HPP

#include <cstdint>
#include <string_view>

namespace sgf::util
{

constexpr std::uint32_t hash(std::string_view str)
{
    std::uint32_t hash = 2166136261u;
    for (char c : str)
    {
        hash ^= static_cast<std::uint32_t>(static_cast<unsigned char>(c));
        hash *= 16777619u;
    }
    return hash;
}

} // namespace sgf::util

#endif