#pragma once

#include <chrono>
#include <sgf/base/window/window_event.hpp>
#include <sgf/input/input_system.hpp>
#include <sgf/partical/partical_system.hpp>
#include <sgf/render_pipeline/render_pipeline.hpp>
#include <sgf/scene/scene.hpp>

class game_scene : public sgf::scene
{
public:
    game_scene(std::uint32_t id) : sgf::scene(id) {}

    void on_init() override
    {
    }

    void on_update(std::chrono::nanoseconds dt) override
    {
        using namespace std::chrono_literals;
        float dt_sec = std::chrono::duration<float>(dt).count();

        auto mouse_pos = sgf::input_system::instance().get_mouse_view_position();

        if (sgf::input_system::instance().is_button_down(sgf::base::mouse_button_code::left))
        {
            for (int i = 0; i < 20; ++i)
            {
                float angle = (std::rand() % 360) * 3.1415926f / 180.0f;
                float speed = (std::rand() % 300 + 100) * 1.0f;
                sgf::type::vec2f vel{std::cos(angle) * speed, std::sin(angle) * speed};

                auto life = 500ms + std::chrono::milliseconds(std::rand() % 700);

                m_particle_system.emit(
                    mouse_pos,
                    vel,
                    sgf::type::color{0, 255, 255, 255},
                    life,
                    sgf::type::color{150, 0, 255, 0});
            }
        }

        m_particle_system.update(dt);
    }

    void on_render(sgf::base::renderer &rd) override
    {
        m_pipeline.submit_particles(m_particle_system.get_particles(), sgf::render_layer::entity);
        m_pipeline.execute(rd);
        m_pipeline.clear();
    }

private:
    sgf::render_pipeline m_pipeline;
    sgf::particle_system m_particle_system;
};