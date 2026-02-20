#include <sgf/render_pipeline/render_pipeline.hpp>

void sgf::render_pipeline::submit(const base::texture &tex, const type::resource_rect &rect, const type::view_rect &dst, std::int16_t z_index)
{
    render_command cmd{};
    cmd.type          = render_type::texture;
    cmd.tex           = &tex;
    cmd.src           = rect;
    cmd.dst           = dst;
    cmd.z_index       = z_index;
    cmd.submission_id = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render_pipeline::submit(const base::texture &tex, const type::view_rect &dst, std::int16_t z_index)
{
    render_command cmd{};
    cmd.type          = render_type::texture;
    cmd.tex           = &tex;
    auto [w, h]       = tex.size();
    cmd.src           = {0, 0, static_cast<float>(w), static_cast<float>(h)};
    cmd.dst           = dst;
    cmd.z_index       = z_index;
    cmd.submission_id = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render_pipeline::submit(const base::texture &tex, const type::resource_rect &src, const type::view_position dst, std::int16_t z_index)
{
    render_command cmd{};
    cmd.type          = render_type::texture;
    cmd.tex           = &tex;
    cmd.src           = src;
    cmd.dst           = {dst.x, dst.y, src.w, src.h};
    cmd.z_index       = z_index;
    cmd.submission_id = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render_pipeline::submit(const base::texture &tex, const type::view_position dst, std::int16_t z_index)
{
    render_command cmd{};
    cmd.type          = render_type::texture;
    cmd.tex           = &tex;
    auto [w, h]       = tex.size();
    cmd.src           = {0, 0, static_cast<float>(w), static_cast<float>(h)};
    cmd.dst           = {dst.x, dst.y, static_cast<float>(w), static_cast<float>(h)};
    cmd.z_index       = z_index;
    cmd.submission_id = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render_pipeline::submit(const resources::sprite &sprite, const type::view_rect &dst, std::int16_t z_index)
{
    render_command cmd{};
    cmd.type          = render_type::sprite;
    cmd.tex           = sprite.texture_ptr;
    cmd.src           = sprite.rect;
    cmd.dst           = dst;
    cmd.pivot         = sprite.pivot;
    cmd.z_index       = z_index;
    cmd.submission_id = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render_pipeline::submit(const resources::sprite &sprite, const type::view_position dst, std::int16_t z_index)
{
    render_command cmd{};
    cmd.type          = render_type::sprite;
    cmd.tex           = sprite.texture_ptr;
    cmd.src           = sprite.rect;
    cmd.dst           = {dst.x, dst.y, sprite.rect.w, sprite.rect.h};
    cmd.pivot         = sprite.pivot;
    cmd.z_index       = z_index;
    cmd.submission_id = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render_pipeline::submit(const type::view_rect &dst, const sgf::type::color &col, graphic_style style, float rotation, std::int16_t z_index)
{
    render_command cmd{};
    cmd.type          = render_type::rect;
    cmd.dst           = dst;
    cmd.color         = col;
    cmd.style         = static_cast<std::uint8_t>(style);
    cmd.rotation      = rotation;
    cmd.z_index       = z_index;
    cmd.submission_id = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render_pipeline::submit(const type::view_rect &dst, graphic_style style, float rotation, std::int16_t z_index)
{
    render_command cmd{};
    cmd.type          = render_type::rect;
    cmd.dst           = dst;
    cmd.style         = static_cast<std::uint8_t>(style);
    cmd.rotation      = rotation;
    cmd.z_index       = z_index;
    cmd.submission_id = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render_pipeline::submit(const type::view_position &center, float radius, const type::color &color, graphic_style style, std::int16_t z_index)
{
    render_command cmd{};
    cmd.type = render_type::circle;

    cmd.dst = {
        center.x,
        center.y,
        radius * 2.0f,
        radius * 2.0f};

    cmd.color         = color;
    cmd.style         = static_cast<std::uint8_t>(style);
    cmd.z_index       = z_index;
    cmd.submission_id = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render_pipeline::execute(base::renderer &rd)
{
    if (p_commands.empty())
        return;

    std::sort(p_commands.begin(), p_commands.end(), [](const render_command &a, const render_command &b)
              {
                  if (a.z_index != b.z_index)
                      return a.z_index < b.z_index;
                  if (a.tex != b.tex)
                      return a.tex < b.tex;
                  return a.submission_id < b.submission_id;
              });

    std::vector<type::vertex> vertex_buffer;
    std::vector<std::int32_t> index_buffer;
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
        if (cmd.tex != current_tex || cmd.style != 1)
        {
            flush();
            current_tex = cmd.tex;
        }

        auto final_dst = rd.get_viewport_ptr()->to_window_rect(cmd.dst);
        type::colorf col{cmd.color};

        float u0 = 0, v0 = 0, u1 = 0, v1 = 0;
        if (cmd.tex)
        {
            auto [tw, th] = cmd.tex->size();
            float inv_w   = 1.0f / tw;
            float inv_h   = 1.0f / th;
            u0            = cmd.src.x * inv_w;
            v0            = cmd.src.y * inv_h;
            u1            = (cmd.src.x + cmd.src.w) * inv_w;
            v1            = (cmd.src.y + cmd.src.h) * inv_h;
        }

        if (cmd.style == 1)
        {
            if (cmd.type == render_type::rect)
            {
                auto base_idx = static_cast<std::int32_t>(vertex_buffer.size());
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
            else if (cmd.type == render_type::circle)
            {
                flush();
                current_tex = cmd.tex;

                auto center_idx = static_cast<std::int32_t>(vertex_buffer.size());
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
        else // Outline 模式 (style == 0)
        {
            // 直接调用原本的描边接口，不走顶点缓冲
            rd.render_rect({final_dst.x - (final_dst.w * cmd.pivot.x),
                            final_dst.y - (final_dst.h * cmd.pivot.y),
                            final_dst.w, final_dst.h},
                           cmd.color, 0);
        }
    }

    flush();
    clear();
}

void sgf::render_pipeline::clear() noexcept
{
    p_commands.clear();
    p_next_id = 1;
}