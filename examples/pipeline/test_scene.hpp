#pragma once

#include <random>
#include <sgf/render_pipeline/render_pipeline.hpp>
#include <sgf/scene/scene.hpp>
#include <sgf/type/color.hpp>
#include <sgf/type/vec2.hpp>
#include <vector>

class test_scene : public sgf::scene
{
public:
    explicit test_scene(std::uint32_t id) : sgf::scene(id) {}

    void on_init() override
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> pos_dist(0.0f, 500.0f);
        std::uniform_real_distribution<float> vel_dist(-60.0f, 60.0f);

        for (int i = 0; i < 1000; ++i)
        {
            m_positions.push_back({pos_dist(gen), pos_dist(gen)});
            m_velocities.push_back({vel_dist(gen), vel_dist(gen)});
            m_colors.push_back({static_cast<uint8_t>(rand() % 256),
                                static_cast<uint8_t>(rand() % 256),
                                static_cast<uint8_t>(rand() % 256),
                                255});
        }
    }

    void on_update(std::chrono::nanoseconds dt) override
    {
        float sec = std::chrono::duration<float>(dt).count();
        for (size_t i = 0; i < m_positions.size(); ++i)
        {
            m_positions[i].x += m_velocities[i].x * sec;
            m_positions[i].y += m_velocities[i].y * sec;

            if (m_positions[i].x < 0 || m_positions[i].x > 490)
                m_velocities[i].x *= -1;
            if (m_positions[i].y < 0 || m_positions[i].y > 490)
                m_velocities[i].y *= -1;
        }
    }

    void on_render(sgf::base::renderer &rd) const override
    {
        m_pipeline.submit({0, 0, 500, 500}, sgf::type::color{40, 44, 52, 255}, sgf::graphic_style::fill, sgf::render_layer::background);

        for (size_t i = 0; i < m_positions.size(); ++i)
        {
            m_pipeline.submit({m_positions[i].x, m_positions[i].y, 10, 10}, m_colors[i], sgf::graphic_style::fill);
        }

        m_pipeline.submit({20, 20, 150, 30}, sgf::type::color::white, sgf::graphic_style::fill, sgf::render_layer::ui);

        m_pipeline.execute(rd);
    }

private:
    std::vector<sgf::type::vec2f> m_positions;
    std::vector<sgf::type::vec2f> m_velocities;
    std::vector<sgf::type::color> m_colors;

    mutable sgf::render_pipeline m_pipeline;
};