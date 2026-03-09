#pragma once
#include <sgf/sgf.hpp>

class static_wall : public sgf::game_object
{
public:
    using sgf::game_object::game_object;

    void on_init(sgf::scene_context &ctx) override
    {
        sgf::physics_config cfg;
        cfg.type = sgf::body_type::static_body;

        sgf::collider_config col;
        col.is_circle   = false;
        col.w           = static_cast<float>(this->size().w);
        col.h           = static_cast<float>(this->size().h);
        col.friction    = 0.5f;
        col.restitution = 0.2f;
        cfg.colliders.push_back(col);

        add_module<sgf::module::physics_module>(ctx, cfg);

        add_module<sgf::module::render_module>(ctx);
    }

    void on_render() override
    {
        auto render = get_module<sgf::module::render_module>();

        sgf::type::view_rect view_rect = {static_cast<float>(position().x),
                                          static_cast<float>(position().y),
                                          static_cast<float>(size().w),
                                          static_cast<float>(size().h)};

        render->pipeline()->submit_rect(
            view_rect,
            sgf::type::color::white,
            sgf::render::style::fill,
            {0.5f, 0.5f},
            rotation(), sgf::render::layer::entity);
    }
};