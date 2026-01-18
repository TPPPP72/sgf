#include <sgf/base/texture.hpp>
#include <sgf/resources/atlas.hpp>
#include <sgf/resources/manager.hpp>
#include <sgf/type/rect.hpp>
#include <stdexcept>
#include <string>

using namespace sgf::resources;

const sprite &atlas::get(std::string_view name) const
{
    auto it = p_sprites.find(std::string{name});

    if (it == p_sprites.end())
        throw std::runtime_error("No name " + std::string{name} + " in atlas!");

    return it->second;
}

atlas atlas_loader::load_from_directory(manager &m, const atlas_directory_info &info)
{
    atlas res;

    for (uint32_t i = 1; i <= info.number; ++i)
    {
        auto &tex = m.load_texture(info.root_path + info.name + std::to_string(i) + "." + info.extension);

        auto [w, h] = tex.size();

        auto key = make_resource_key(info, i);

        auto it = res.p_sprites.find(key);

        if (it != res.p_sprites.end())
            throw std::runtime_error("Atlas frame conflicted:" + key);

        auto [pos, inserted] = res.p_sprites.try_emplace(key, &tex, type::resource_rect{0, 0, static_cast<double>(w), static_cast<double>(h)}, info.pivot);
    }

    return res;
}

atlas atlas_loader::load_from_sheet(manager &m, const atlas_sheet_info &info)
{
    atlas res;

    auto &tex     = m.load_texture(info.path);
    auto [rw, rh] = tex.size();

    double ew = static_cast<double>(rw) / info.col;
    double eh = static_cast<double>(rh) / info.row;

    std::uint32_t count = 0;
    for (std::uint32_t row = 0; row < info.row; ++row)
    {
        for (std::uint32_t col = 0; col < info.col; ++col)
        {
            ++count;

            auto key = make_resource_key(info, count);

            auto it = res.p_sprites.find(key);

            if (it != res.p_sprites.end())
                throw std::runtime_error("Atlas frame conflicted:" + key);

            auto [pos, inserted] = res.p_sprites.try_emplace(key, &tex, type::resource_rect{col * ew, row * eh, ew, eh}, info.pivot);
        }
    }

    return res;
}

std::string atlas_loader::make_resource_key(const atlas_directory_info &info, std::uint32_t current_frame)
{
    auto root_path = info.root_path;
    std::replace(root_path.begin(), root_path.end(), '/', '_');
    std::replace(root_path.begin(), root_path.end(), '\\', '_');
    return root_path + info.name + std::to_string(current_frame);
}

std::string atlas_loader::make_resource_key(const atlas_sheet_info &info, std::uint32_t current_frame)
{
    auto path = info.path;
    std::replace(path.begin(), path.end(), '/', '_');
    std::replace(path.begin(), path.end(), '\\', '_');
    return path.substr(0, path.rfind(".")) + std::to_string(current_frame);
}