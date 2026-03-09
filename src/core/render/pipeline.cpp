#include <sgf/base/texture.hpp>
#include <sgf/render/pipeline.hpp>
#include <sgf/resource/manager.hpp>

void sgf::render::pipeline::submit(sgf::type::uint32 tex_key, const sgf::type::resource_rect &src, const sgf::type::view_rect &dst, const sgf::type::vec2f &pivot, float rot, sgf::type::int16 z)
{
    render::command cmd{};
    cmd.submission_type = render::type::texture;
    cmd.texture_key     = tex_key;
    cmd.src             = src;
    cmd.pivot           = pivot;
    cmd.dst             = dst;
    cmd.z_index         = z;
    cmd.rotation        = rot;
    cmd.submission_id   = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render::pipeline::submit_rect(const sgf::type::view_rect &dst, const sgf::type::color &col, style st, const sgf::type::vec2f &pivot, float rotation, sgf::type::int16 z_index)
{
    render::command cmd{};
    cmd.submission_type = render::type::rect;
    cmd.dst             = dst;
    cmd.color           = col;
    cmd.style           = static_cast<std::uint8_t>(st);
    cmd.rotation        = rotation;
    cmd.pivot           = pivot;
    cmd.z_index         = z_index;
    cmd.submission_id   = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render::pipeline::submit_circle(const sgf::type::view_position &center, float radius, const sgf::type::color &color, style st, sgf::type::int16 z_index)
{
    render::command cmd{};
    cmd.submission_type = render::type::circle;

    cmd.dst = {
        center.x,
        center.y,
        radius * 2.0f,
        radius * 2.0f};

    cmd.color         = color;
    cmd.style         = static_cast<std::uint8_t>(st);
    cmd.z_index       = z_index;
    cmd.submission_id = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render::pipeline::submit_particles(const std::array<particle::data, 1000> &pool, sgf::type::int16 z_index)
{
    for (const auto &p : pool)
    {
        if (!p.active)
            continue;

        render::command cmd{};
        cmd.submission_type = render::type::rect;
        cmd.dst             = {p.pos.x - 1.0f, p.pos.y - 1.0f, 2.0f, 2.0f};

        cmd.color         = p.current_color;
        cmd.style         = 1;
        cmd.z_index       = z_index;
        cmd.submission_id = p_next_id++;

        p_commands.emplace_back(cmd);
    }
}

void sgf::render::pipeline::execute(base::renderer &rd, resource::manager *const mgr)
{
    if (p_commands.empty())
        return;

    std::sort(p_commands.begin(), p_commands.end(), [mgr](const render::command &a, const render::command &b)
              {
                  if (a.z_index != b.z_index)
                      return a.z_index < b.z_index;

                  if (mgr)
                  {
                      auto a_tex = mgr->get<base::texture>(a.texture_key);
                      auto b_tex = mgr->get<base::texture>(b.texture_key);
                      if (a_tex != b_tex)
                          return a_tex < b_tex;
                  }

                  return a.submission_id < b.submission_id;
              });

    std::vector<sgf::type::vertex> vertex_buffer;
    std::vector<sgf::type::int32> index_buffer;
    vertex_buffer.reserve(p_commands.size() * 4);
    index_buffer.reserve(p_commands.size() * 6);

    const base::texture *current_tex = nullptr;

    auto flush = [&]()
    {
        if (vertex_buffer.empty())
            return;
        rd.render_geometry(current_tex, vertex_buffer.data(), static_cast<int32_t>(vertex_buffer.size()), index_buffer.data(), static_cast<int32_t>(index_buffer.size()));
        vertex_buffer.clear();
        index_buffer.clear();
    };

    for (const auto &cmd : p_commands)
    {
        base::texture *cmd_tex = mgr ? mgr->get<base::texture>(cmd.texture_key) : nullptr;
        if (cmd_tex != current_tex || cmd.style != 1)
        {
            flush();
            current_tex = cmd_tex;
        }

        auto final_dst = rd.get_viewport_ptr()->to_window_rect(cmd.dst);
        sgf::type::colorf col{cmd.color};

        float u0 = 0, v0 = 0, u1 = 0, v1 = 0;
        if (cmd_tex)
        {
            auto [tw, th] = cmd_tex->size();
            float inv_w   = 1.0f / tw;
            float inv_h   = 1.0f / th;
            u0            = cmd.src.x * inv_w;
            v0            = cmd.src.y * inv_h;
            u1            = (cmd.src.x + cmd.src.w) * inv_w;
            v1            = (cmd.src.y + cmd.src.h) * inv_h;
        }

        if (cmd.style == 1)
        {
            if (cmd.submission_type == render::type::rect)
            {
                auto base_idx = static_cast<sgf::type::int32>(vertex_buffer.size());
                float cos_a   = std::cos(cmd.rotation);
                float sin_a   = std::sin(cmd.rotation);

                float x_off[4]   = {-final_dst.w * cmd.pivot.x, final_dst.w * (1.0f - cmd.pivot.x), -final_dst.w * cmd.pivot.x, final_dst.w * (1.0f - cmd.pivot.x)};
                float y_off[4]   = {-final_dst.h * cmd.pivot.y, -final_dst.h * cmd.pivot.y, final_dst.h * (1.0f - cmd.pivot.y), final_dst.h * (1.0f - cmd.pivot.y)};
                float u_coord[4] = {u0, u1, u0, u1};
                float v_coord[4] = {v0, v0, v1, v1};

                for (int i = 0; i < 4; ++i)
                {
                    float rx = x_off[i] * cos_a - y_off[i] * sin_a + final_dst.x;
                    float ry = x_off[i] * sin_a + y_off[i] * cos_a + final_dst.y;
                    vertex_buffer.push_back({{rx, ry}, col, {u_coord[i], v_coord[i]}});
                }

                index_buffer.insert(index_buffer.end(), {base_idx + 0, base_idx + 1, base_idx + 2, base_idx + 1, base_idx + 3, base_idx + 2});
            }
            else if (cmd.submission_type == sgf::render::type::circle)
            {
                flush();
                current_tex = cmd_tex;

                auto center_idx = static_cast<sgf::type::int32>(vertex_buffer.size());
                float radius    = final_dst.w * 0.5f;
                int segments    = 32;

                float mid_u   = (u0 + u1) * 0.5f;
                float mid_v   = (v0 + v1) * 0.5f;
                float half_uw = (u1 - u0) * 0.5f;
                float half_vh = (v1 - v0) * 0.5f;

                vertex_buffer.push_back({{final_dst.x, final_dst.y}, col, {mid_u, mid_v}});

                for (int i = 0; i <= segments; ++i)
                {
                    float angle = i * 2.0f * 3.1415926f / segments;
                    float vx    = final_dst.x + std::cos(angle) * radius;
                    float vy    = final_dst.y + std::sin(angle) * radius;

                    float uv_angle = angle + cmd.rotation;
                    float vu       = mid_u + std::cos(uv_angle) * half_uw;
                    float vv       = mid_v + std::sin(uv_angle) * half_vh;

                    vertex_buffer.push_back({{vx, vy}, col, {vu, vv}});

                    if (i > 0)
                    {
                        index_buffer.push_back(center_idx);
                        index_buffer.push_back(center_idx + i);
                        index_buffer.push_back(center_idx + i + 1);
                    }
                }
                flush();
            }
        }
        else
        {
            rd.render_rect({final_dst.x - (final_dst.w * cmd.pivot.x),
                            final_dst.y - (final_dst.h * cmd.pivot.y),
                            final_dst.w, final_dst.h},
                           cmd.color, 0);
        }
    }

    flush();
    clear();
}

void sgf::render::pipeline::clear() noexcept
{
    p_commands.clear();
    p_next_id = 1;
}