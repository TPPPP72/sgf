#include <sgf/context/scene_context.hpp>
#include <sgf/game_object/modules/render_module.hpp>
#include <sgf/render/pipeline.hpp>
#include <sgf/scene/scene.hpp>

sgf::render::pipeline *sgf::module::render_module::pipeline() noexcept
{
    return this->context().pipe;
}