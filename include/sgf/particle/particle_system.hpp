#ifndef SGF_PARTICAL_SYSTEM_HPP
#define SGF_PARTICAL_SYSTEM_HPP

#include <array>
#include <chrono>
#include <optional>
#include <sgf/type/color.hpp>
#include <sgf/type/vec2.hpp>

namespace sgf
{

struct particle
{
    sgf::type::vec2f pos;
    sgf::type::vec2f vel;
    sgf::type::color start_color;
    sgf::type::color end_color;
    sgf::type::color current_color;
    std::chrono::nanoseconds life     = std::chrono::nanoseconds(0);
    std::chrono::nanoseconds max_life = std::chrono::nanoseconds(0);
    bool active                       = false;
};

class particle_system
{
public:
    template <typename Rep, typename Period>
    void emit(sgf::type::vec2f pos,
              sgf::type::vec2f vel,
              sgf::type::color start_col,
              std::chrono::duration<Rep, Period> life_duration,
              std::optional<sgf::type::color> end_col = std::nullopt)
    {
        auto life_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(life_duration);

        for (auto &p : m_pool)
        {
            if (!p.active)
            {
                p.pos           = pos;
                p.vel           = vel;
                p.start_color   = start_col;
                p.end_color     = end_col.value_or(start_col);
                p.current_color = start_col;
                p.life = p.max_life = life_ns;
                p.active            = true;
                return;
            }
        }
    }

    void update(std::chrono::nanoseconds dt)
    {
        for (auto &p : m_pool)
        {
            if (!p.active)
                continue;

            p.life -= dt;
            if (p.life <= std::chrono::nanoseconds(0))
            {
                p.active = false;
                continue;
            }

            float dt_sec = std::chrono::duration<float>(dt).count();
            p.pos.x += p.vel.x * dt_sec;
            p.pos.y += p.vel.y * dt_sec;

            float t = 1.0f - (static_cast<float>(p.life.count()) / p.max_life.count());

            p.current_color.r = static_cast<std::uint8_t>(p.start_color.r * (1.0f - t) + p.end_color.r * t);
            p.current_color.g = static_cast<std::uint8_t>(p.start_color.g * (1.0f - t) + p.end_color.g * t);
            p.current_color.b = static_cast<std::uint8_t>(p.start_color.b * (1.0f - t) + p.end_color.b * t);
            p.current_color.a = static_cast<std::uint8_t>(p.start_color.a * (1.0f - t) + p.end_color.a * t);
        }
    }

    const std::array<particle, 1000> &get_particles() const { return m_pool; }

private:
    std::array<particle, 1000> m_pool;
};

} // namespace sgf

#endif