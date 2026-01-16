#ifndef SGF_RESOURCES_ATLAS_HPP
#define SGF_RESOURCES_ATLAS_HPP

#include "sprite.hpp"
#include <string>
#include <unordered_map>

namespace sgf::resources
{

class atlas
{
public:
    const sprite &get(std::string_view name) const;

private:
    std::unordered_map<std::string, sprite> p_sprites;
};

} // namespace sgf::resources

#endif