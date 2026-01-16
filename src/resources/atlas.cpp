#include <sgf/resources/atlas.hpp>
#include <stdexcept>

using namespace sgf::resources;

const sprite &atlas::get(std::string_view name) const
{
    auto it = p_sprites.find(std::string{name});

    if (it == p_sprites.end())
        throw std::runtime_error("No name " + std::string{name} + " in atlas!");

    return it->second;
}