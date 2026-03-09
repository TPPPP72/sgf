#pragma once

#include <sgf/sgf.hpp>

class game_scene : public sgf::scene
{
public:
    game_scene(std::uint32_t id) : sgf::scene(id) {}

    void on_init() override
    {
    }

    void on_input(const sgf::input_event &e) override
    {
        if (e.type == sgf::base::event_type::mouse_button_down && e.mouse == sgf::base::mouse_button_code::left)
        {
            m_begin_color = sgf::util::make_random_color<sgf::type::color>();
            m_end_color   = sgf::util::make_random_color<sgf::type::color>();
        }
    }

    void on_update(const sgf::frame_context &ctx) override
    {
        using namespace std::chrono_literals;

        for (int i = 0; i < 20; ++i)
        {
            float angle = (std::rand() % 360) * 3.1415926f / 180.0f;
            float speed = (std::rand() % 300 + 100) * 1.0f;
            sgf::type::vec2f vel{std::cos(angle) * speed, std::sin(angle) * speed};

            auto life = 500ms + std::chrono::milliseconds(std::rand() % 700);

            m_particle_manager.emit(
                ctx.mouse_view_pos,
                vel,
                m_begin_color,
                life,
                m_end_color);
        }

        m_particle_manager.update(ctx.dt);
    }

    void on_render(sgf::base::renderer &rd) override
    {
        m_pipeline.submit_particles(m_particle_manager.get_particles(), sgf::render::layer::entity);
        m_pipeline.execute(rd, nullptr);
    }

private:
    sgf::render::pipeline m_pipeline;
    sgf::particle::manager m_particle_manager;
    sgf::type::color m_begin_color{0, 255, 255, 255};
    sgf::type::color m_end_color{150, 0, 255, 0};
};