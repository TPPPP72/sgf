#pragma once
#include "sgf/type/rect.hpp"
#include <sgf/game_object/game_object.hpp>
#include <sgf/game_object/modules/camera_module.hpp>
#include <sgf/game_object/modules/physics_module.hpp>
#include <sgf/game_object/modules/render_module.hpp>
#include <sgf/physics/physics_config.hpp>
#include <sgf/type/color.hpp>

class ball : public sgf::game_object
{
public:
    using sgf::game_object::game_object;

    void on_init(sgf::scene_context &ctx) override
    {
        this->size() = {40, 40};

        sgf::physics_config cfg;
        cfg.type = sgf::body_type::dynamic_body;

        sgf::collider_config col;
        col.is_circle   = true;
        col.radius      = 20.0f;
        col.restitution = 0.7f;
        col.friction    = 0.3f;
        cfg.colliders.push_back(col);

        add_module<sgf::module::physics_module>(ctx, cfg);
        add_module<sgf::module::render_module>(ctx);
    }

    void on_render() override
    {
        auto render = get_module<sgf::module::render_module>();

        auto [x, y] = this->position();
        auto rot    = this->rotation();

        sgf::type::view_rect view_rect = {static_cast<float>(x),
                                          static_cast<float>(y),
                                          static_cast<float>(size().w),
                                          static_cast<float>(size().h)};

        render->pipeline()->submit({static_cast<float>(x), static_cast<float>(y)}, 20.0f, sgf::type::color::red, sgf::graphic_style::fill);
    }
};