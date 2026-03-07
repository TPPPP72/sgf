#ifndef SGF_RESOURCE_DATA_HPP
#define SGF_RESOURCE_DATA_HPP

#include <cstdint>
#include <sgf/type/rect.hpp>
#include <sgf/type/vec2.hpp>
#include <vector>
#include <string>

namespace sgf::resource
{

struct asset
{
    std::uint32_t type;
    std::string path;
    std::uint32_t key;
};

struct sprite
{
    std::uint32_t atlas;
    std::uint32_t key;
    sgf::type::vec2f pivot;
    sgf::type::resource_rect src;
};

struct atlas
{
    std::uint32_t texture;
    std::uint32_t key;
    std::uint32_t number;
    std::vector<sprite> sprites;
};

struct frame
{
    std::uint32_t sprite;
    sgf::type::vec2f offset;
    sgf::type::view_rect hurt_box;
    sgf::type::view_rect attack_box;
    float msec;
};

struct animation
{
    std::uint32_t key;
    std::uint32_t number;
    std::vector<frame> frames;
};

} // namespace sgf::resource

#endif