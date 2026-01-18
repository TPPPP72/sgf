#ifndef SGF_RESOURCES_MANAGER_HPP
#define SGF_RESOURCES_MANAGER_HPP

#include "../base/audio/audio.hpp"
#include "../base/font.hpp"
#include "../base/texture.hpp"
#include "atlas.hpp"
#include "sprite.hpp"
#include <filesystem>
#include <unordered_map>

namespace sgf::resources
{

class manager
{
public:
    manager(const manager &)            = delete;
    manager &operator=(const manager &) = delete;
    const base::audio &load_audio(const std::filesystem::path &);
    const base::font &load_font(const std::filesystem::path &);
    const base::texture &load_texture(const std::filesystem::path &);
    const sprite &load_sprite(const std::filesystem::path &);
    const atlas &load_atlas_from_directory(const std::filesystem::path &);
    const atlas &load_atlas_from_sheet(const std::filesystem::path &);

private:
    std::unordered_map<std::string, base::audio> p_audios;
    std::unordered_map<std::string, base::font> p_fonts;
    std::unordered_map<std::string, base::texture> p_textures;
    std::unordered_map<std::string, sprite> p_sprites;
    std::unordered_map<std::string, atlas> p_atlases;
};

} // namespace sgf::resources

#endif