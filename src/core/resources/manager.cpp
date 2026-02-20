#include <sgf/base/audio/audio.hpp>
#include <sgf/base/texture.hpp>
#include <sgf/resources/atlas.hpp>
#include <sgf/resources/manager.hpp>
#include <sgf/resources/sprite.hpp>
#include <sgf/type/vec2.hpp>

using namespace sgf::resources;
using namespace sgf::base;

template <typename T, typename Container, typename... Args>
const T &get_or_load(Container &cache, const std::string &key, Args &&...args)
{
    auto it = cache.find(key);
    if (it == cache.end())
    {
        auto [new_it, success] = cache.emplace(
            std::piecewise_construct,
            std::forward_as_tuple(key),
            std::forward_as_tuple(std::forward<Args>(args)...));
        return new_it->second;
    }
    return it->second;
}

const audio &manager::load_audio(const std::filesystem::path &p)
{
    return get_or_load<audio>(p_audios, p.string(), p);
}

const font &manager::load_font(const std::filesystem::path &p, std::uint32_t size)
{
    return get_or_load<font>(p_fonts, p.string(), p, size);
}

const texture &manager::load_texture(const std::filesystem::path &p)
{
    return get_or_load<texture>(p_textures, p.string(), p_renderer, p);
}

const sprite &manager::load_sprite(const std::filesystem::path &p)
{
    auto &tex   = load_texture(p);
    auto [w, h] = tex.size();

    return get_or_load<sprite>(p_sprites, p.string(), &tex,
                               type::resource_rect{0.0, 0.0, static_cast<float>(w), static_cast<float>(h)},
                               type::vec2f{0.5, 0.5});
}

const atlas &manager::load_atlas_from_directory(const atlas_directory_info &info)
{
    return get_or_load<atlas>(p_atlases, info.root_path,
                              atlas_loader{}.load_from_directory(*this, info));
}

const atlas &manager::load_atlas_from_sheet(const atlas_sheet_info &info)
{
    return get_or_load<atlas>(p_atlases, info.path.substr(0, info.path.rfind(".")),
                              atlas_loader{}.load_from_sheet(*this, info));
}