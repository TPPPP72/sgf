#ifndef SGF_RENDER_PIPELINE_HPP
#define SGF_RENDER_PIPELINE_HPP

#include <sgf/particle/particle_system.hpp>
#include <sgf/type/color.hpp>
#include <sgf/type/position.hpp>
#include <sgf/type/rect.hpp>
#include <vector>

namespace sgf
{

namespace base
{
class renderer;
}

namespace resource
{
class manager;
}

enum class graphic_style : std::uint8_t
{
    outline,
    fill
};

enum class render_type : std::uint8_t
{
    texture,
    rect,
    circle
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
    type::resource_rect src;
    type::view_rect dst;
    type::vec2f pivot;
    float rotation{0.0f};

    std::uint32_t texture_key;
    std::uint32_t submission_id;

    type::color color;
    std::int16_t z_index;
    render_type type;
    std::uint8_t style;
};

class render_pipeline
{
public:
    render_pipeline()
    {
        p_commands.reserve(2048);
    }
    void submit(uint32_t tex_key, const type::resource_rect &src, const type::view_rect &dst, const type::vec2f &pivot, float rot, std::int16_t z);
    void submit_rect(const type::view_rect &, const sgf::type::color &, graphic_style, const type::vec2f &pivot, float rotation, std::int16_t z_index);
    void submit_circle(const type::view_position &center, float radius, const type::color &color, graphic_style, std::int16_t z_index);
    void submit_particles(const std::array<particle, 1000> &pool, std::int16_t z_index);
    void execute(base::renderer &rd, resource::manager *const mgr);
    void clear() noexcept;

private:
    std::vector<render_command> p_commands;
    std::uint32_t p_next_id{1};
};

} // namespace sgf

#endif