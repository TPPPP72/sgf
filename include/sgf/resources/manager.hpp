#ifndef SGF_RESOURCES_MANAGER_HPP
#define SGF_RESOURCES_MANAGER_HPP

#include "../base/audio/audio.hpp"
#include "../base/font.hpp"
#include "../base/texture.hpp"
#include "atlas.hpp"
#include "sgf/base/renderer.hpp"
#include "sprite.hpp"
#include <filesystem>
#include <unordered_map>

namespace sgf::resources
{

class manager
{
public:
    manager(base::renderer &renderer) : p_renderer(renderer) {}
    ~manager()                          = default;
    manager(const manager &)            = delete;
    manager &operator=(const manager &) = delete;
    manager(manager &&)                 = delete;
    manager &operator=(manager &&)      = delete;
    const base::audio &load_audio(const std::filesystem::path &);
    const base::font &load_font(const std::filesystem::path &, std::uint32_t size);
    const base::texture &load_texture(const std::filesystem::path &);
    const sprite &load_sprite(const std::filesystem::path &);
    const atlas &load_atlas_from_directory(const atlas_directory_info &);
    const atlas &load_atlas_from_sheet(const atlas_sheet_info &);

private:
    std::unordered_map<std::string, base::audio> p_audios;
    std::unordered_map<std::string, base::font> p_fonts;
    std::unordered_map<std::string, base::texture> p_textures;
    std::unordered_map<std::string, sprite> p_sprites;
    std::unordered_map<std::string, atlas> p_atlases;
    base::renderer &p_renderer;
};

} // namespace sgf::resources

#endif