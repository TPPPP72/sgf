#ifndef SGF_RESOURCE_DATA_HPP
#define SGF_RESOURCE_DATA_HPP

#include <sgf/type/int.hpp>
#include <sgf/type/rect.hpp>
#include <sgf/type/vec2.hpp>
#include <string>
#include <vector>

namespace sgf
{

class render_pipeline;

namespace resource
{

class manager;

struct asset
{
    sgf::type::uint32 type;
    std::string path;
    sgf::type::uint32 key;
};

struct sprite
{
    sgf::type::uint32 atlas;
    sgf::type::uint32 key;
    sgf::type::vec2f pivot;
    sgf::type::resource_rect src;
};

struct atlas
{
    sgf::type::uint32 texture;
    sgf::type::uint32 key;
    sgf::type::uint32 number;
    std::vector<sprite> sprites;
};

struct frame
{
    sgf::type::uint32 sprite;
    sgf::type::vec2f offset;
    sgf::type::view_rect hurt_box;
    sgf::type::view_rect attack_box;
    float msec;
};

struct animation
{
    sgf::type::uint32 key;
    sgf::type::uint32 number;
    std::vector<frame> frames;
};

} // namespace resource

} // namespace sgf

#endif