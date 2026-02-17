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

void sgf::render_pipeline::submit(const type::view_rect &dst, const sgf::type::color &col, graphic_style style, std::int16_t z_index)
{
    render_command cmd{};
    cmd.type          = render_type::rect;
    cmd.dst           = dst;
    cmd.color         = col;
    cmd.style         = static_cast<std::uint8_t>(style);
    cmd.z_index       = z_index;
    cmd.submission_id = p_next_id;
    ++p_next_id;

    p_commands.emplace_back(cmd);
}

void sgf::render_pipeline::submit(const type::view_rect &dst, graphic_style style, std::int16_t z_index)
{
    render_command cmd{};
    cmd.type          = render_type::rect;
    cmd.dst           = dst;
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

        rd.render_geometry(current_tex,
                           vertex_buffer.data(), static_cast<int32_t>(vertex_buffer.size()),
                           index_buffer.data(), static_cast<int32_t>(index_buffer.size()));

        vertex_buffer.clear();
        index_buffer.clear();
    };

    for (const auto &cmd : p_commands)
    {
        if (cmd.tex != current_tex)
        {
            flush();
            current_tex = cmd.tex;
        }

        float fx = cmd.dst.x - (cmd.dst.w * cmd.pivot.x);
        float fy = cmd.dst.y - (cmd.dst.h * cmd.pivot.y);
        float fw = cmd.dst.w;
        float fh = cmd.dst.h;

        if (cmd.type == render_type::texture || cmd.type == render_type::sprite || cmd.type == render_type::rect)
        {
            auto base_idx = static_cast<std::int32_t>(vertex_buffer.size());

            float u0 = 0, v0 = 0, u1 = 0, v1 = 0;
            if (cmd.tex)
            {
                float tw = static_cast<float>(cmd.tex->size().w);
                float th = static_cast<float>(cmd.tex->size().h);
                u0       = cmd.src.x / tw;
                v0       = cmd.src.y / th;
                u1       = (cmd.src.x + cmd.src.w) / tw;
                v1       = (cmd.src.y + cmd.src.h) / th;
            }

            type::colorf col{cmd.color};
            vertex_buffer.push_back({{fx, fy}, col, {u0, v0}});
            vertex_buffer.push_back({{fx + fw, fy}, col, {u1, v0}});
            vertex_buffer.push_back({{fx, fy + fh}, col, {u0, v1}});
            vertex_buffer.push_back({{fx + fw, fy + fh}, col, {u1, v1}});

            index_buffer.emplace_back(base_idx + 0);
            index_buffer.emplace_back(base_idx + 1);
            index_buffer.emplace_back(base_idx + 2);
            index_buffer.emplace_back(base_idx + 1);
            index_buffer.emplace_back(base_idx + 3);
            index_buffer.emplace_back(base_idx + 2);
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