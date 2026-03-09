#ifndef SGF_RENDER_PIPELINE_HPP
#define SGF_RENDER_PIPELINE_HPP

#include <sgf/particle/manager.hpp>
#include <sgf/type/color.hpp>
#include <sgf/type/int.hpp>
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

namespace render
{

enum class style : sgf::type::uint8
{
    outline,
    fill
};

enum class type : sgf::type::uint8
{
    texture,
    rect,
    circle
};

enum layer : sgf::type::int16
{
    background = -1000,
    env        = 0,
    entity     = 1000,
    foreground = 2000,
    ui         = 3000
};

struct command
{
    sgf::type::resource_rect src;
    sgf::type::view_rect dst;
    sgf::type::vec2f pivot;
    float rotation{0.0f};

    sgf::type::uint32 texture_key;
    sgf::type::uint32 submission_id;

    sgf::type::color color;
    sgf::type::int16 z_index;
    type submission_type;
    sgf::type::uint8 style;
};

class pipeline
{
public:
    pipeline()
    {
        p_commands.reserve(2048);
    }
    void submit(sgf::type::uint32 tex_key, const sgf::type::resource_rect &src, const sgf::type::view_rect &dst, const sgf::type::vec2f &pivot, float rot, sgf::type::int16 z);
    void submit_rect(const sgf::type::view_rect &, const sgf::type::color &, style, const sgf::type::vec2f &pivot, float rotation, sgf::type::int16 z_index);
    void submit_circle(const sgf::type::view_position &center, float radius, const sgf::type::color &color, style, sgf::type::int16 z_index);
    void submit_particles(const std::array<particle::data, 1000> &pool, sgf::type::int16 z_index);
    void execute(base::renderer &rd, resource::manager *const mgr);
    void clear() noexcept;

private:
    std::vector<command> p_commands;
    sgf::type::uint32 p_next_id{1};
};

} // namespace render

} // namespace sgf

#endif