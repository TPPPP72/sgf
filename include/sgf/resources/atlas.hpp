#ifndef SGF_RESOURCES_ATLAS_HPP
#define SGF_RESOURCES_ATLAS_HPP

#include "sprite.hpp"
#include <string>
#include <unordered_map>

namespace sgf::resources
{

class manager;

class atlas
{
public:
    const sprite &get(std::string_view name) const;

private:
    std::unordered_map<std::string, sprite> p_sprites;
    friend class atlas_loader;
};

struct atlas_directory_info
{
    std::string root_path;
    std::string name;
    std::uint32_t number;
    std::string extension;
    type::vec2 pivot{0.5, 0.5};
};

struct atlas_sheet_info
{
    std::string path;
    std::uint32_t row = 1;
    std::uint32_t col = 1;
    type::vec2 pivot{0.5, 0.5};
};

class atlas_loader
{
public:
    atlas load_from_directory(manager &, const atlas_directory_info &);
    atlas load_from_sheet(manager &, const atlas_sheet_info &);

private:
    std::string make_resource_key(const atlas_directory_info &, std::uint32_t current_frame);
    std::string make_resource_key(const atlas_sheet_info &, std::uint32_t current_frame);
};

} // namespace sgf::resources

#endif