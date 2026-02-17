#ifndef SGF_RENDER_PIPELINE_HPP
#define SGF_RENDER_PIPELINE_HPP

#include "../base/renderer.hpp"
#include "../base/texture.hpp"
#include "../resources/sprite.hpp"
#include "../type/color.hpp"
#include "../type/position.hpp"
#include "../type/rect.hpp"

namespace sgf
{

enum class graphic_style : std::uint8_t
{
    outline,
    fill
};

enum class render_type : std::uint8_t
{
    texture,
    sprite,
    rect
};

enum render_layer : std::int16_t
{
    background = -1000,
    env        = 0,
    entity     = 1000,
    foreground = 2000,
    ui         = 3000
};

struct render_command
{
    const base::texture *tex{nullptr};

    type::resource_rect src;
    type::view_rect dst;
    type::vec2f pivot{0.5, 0.5};

    std::uint32_t submission_id;

    std::int16_t z_index;

    render_type type;
    std::uint8_t style;
    type::color color;
};

class render_pipeline
{
public:
    render_pipeline()
    {
        p_commands.reserve(512);
    }
    void submit(const base::texture &, const type::resource_rect &, const type::view_rect &dst, std::int16_t z_index = entity);
    void submit(const base::texture &, const type::view_rect &dst, std::int16_t z_index = entity);
    void submit(const base::texture &, const type::resource_rect &, const type::view_position dst, std::int16_t z_index = entity);
    void submit(const base::texture &, const type::view_position dst, std::int16_t z_index = entity);
    void submit(const resources::sprite &, const type::view_rect &dst, std::int16_t z_index = entity);
    void submit(const resources::sprite &, const type::view_position dst, std::int16_t z_index = entity);
    void submit(const type::view_rect &, const sgf::type::color &, graphic_style, std::int16_t z_index = entity);
    void submit(const type::view_rect &, graphic_style, std::int16_t z_index = entity);
    void execute(base::renderer &rd);
    void clear() noexcept;

private:
    std::vector<render_command> p_commands;
    std::uint32_t p_next_id{1};
};

} // namespace sgf

#endif