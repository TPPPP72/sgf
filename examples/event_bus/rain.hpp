#pragma once
#include <cstdlib>
#include <sgf/event/event.hpp>
#include <sgf/game_object/game_object.hpp>
#include <sgf/game_object/modules/camera_module.hpp>
#include <sgf/game_object/modules/event_module.hpp>
#include <sgf/game_object/modules/physics_module.hpp>
#include <sgf/game_object/modules/render_module.hpp>
#include <sgf/physics/physics_config.hpp>
#include <sgf/type/color.hpp>
#include <sgf/type/rect.hpp>

class rain : public sgf::game_object
{
public:
    using sgf::game_object::game_object;

    void on_init(sgf::scene_context &ctx) override
    {
        m_color = sgf::type::color::white;

        sgf::physics_config cfg;
        cfg.type = sgf::body_type::dynamic_body;

        sgf::collider_config col;
        col.is_circle   = true;
        col.radius      = 5.0f;
        col.restitution = 0.6f;
        col.friction    = 0.1f;
        cfg.colliders.push_back(col);

        auto physic_module = add_module<sgf::module::physics_module>(ctx, cfg);
        add_module<sgf::module::render_module>(ctx);
        add_module<sgf::module::camera_module>(ctx);
        auto event_module = add_module<sgf::module::event_module>(ctx);

        auto random_color = []()
        {
            return sgf::type::color{
                static_cast<uint8_t>(std::rand() % 128 + 128),
                static_cast<uint8_t>(std::rand() % 128 + 128),
                static_cast<uint8_t>(std::rand() % 128 + 128),
                255};
        };

        event_module->bus()->subscribe<sgf::event::collision_begin>([this, physic_module, random_color](auto &e)
                                                                    {
                                                                        uint32_t my_id = this->id();

                                                                        // 过滤无关事件
                                                                        if (e.id_a != my_id && e.id_b != my_id)
                                                                            return;

                                                                        uint32_t other_id = (e.id_a == my_id) ? e.id_b : e.id_a;

                                                                        this->m_color = random_color();

                                                                        // 传送重置 (撞到传感器 103)
                                                                        if (other_id == 103)
                                                                        {
                                                                            float rx = 250.0f + static_cast<float>(std::rand() % 300);
                                                                            float ry = -100.0f;

                                                                            this->position() = {rx, ry};

                                                                            physic_module->sync_to_physics();
                                                                            physic_module->set_linear_velocity({0, 0});
                                                                        }
                                                                    });
    }

    void on_render() override
    {
        auto render = get_module<sgf::module::render_module>();
        auto camera = get_module<sgf::module::camera_module>();

        auto *main_cam = camera->get_main();

        auto view_pos = main_cam->to_view_pos(position());

        render->pipeline()->submit(
            view_pos,
            5.0f,    // 半径
            m_color, // 碰撞后改变的颜色
            sgf::graphic_style::fill);
    }

private:
    sgf::type::color m_color;
};