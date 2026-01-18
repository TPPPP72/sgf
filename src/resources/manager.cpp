#include <sgf/base/audio/audio.hpp>
#include <sgf/base/texture.hpp>
#include <sgf/resources/manager.hpp>
#include <sgf/resources/sprite.hpp>
#include <sgf/type/vec2.hpp>

using namespace sgf::resources;
using namespace sgf::base;

const audio &manager::load_audio(const std::filesystem::path &p)
{
    auto key = p.string();

    auto it = p_audios.find(key);

    if (it != p_audios.end())
        return it->second;

    auto [pos, inserted] = p_audios.try_emplace(key, p);
    return pos->second;
}

const font &manager::load_font(const std::filesystem::path &p)
{
    auto key = p.string();

    auto it = p_fonts.find(key);

    if (it != p_fonts.end())
        return it->second;

    auto [pos, inserted] = p_fonts.try_emplace(key, p);
    return pos->second;
}

const texture &manager::load_texture(const std::filesystem::path &p)
{
    auto key = p.string();

    auto it = p_textures.find(key);

    if (it != p_textures.end())
        return it->second;

    auto [pos, inserted] = p_textures.try_emplace(key, p);
    return pos->second;
}

const sprite &manager::load_sprite(const std::filesystem::path &p)
{
    auto key = p.string();

    auto it = p_sprites.find(key);

    if (it != p_sprites.end())
        return it->second;

    auto &texture = this->load_texture(p);

    auto [w, h] = texture.size();

    auto [pos, inserted] = p_sprites.try_emplace(key, &texture, type::resource_rect{0, 0, static_cast<double>(w), static_cast<double>(h)}, type::vec2{0.5, 0.5});
    return pos->second;
}