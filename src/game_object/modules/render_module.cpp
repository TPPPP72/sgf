#include <sgf/game_object/modules/render_module.hpp>
#include <sgf/render_pipeline/render_pipeline.hpp>
#include <sgf/scene/scene.hpp>

sgf::render_pipeline &sgf::module::render_module::pipeline() noexcept
{
    return this->context().pipeline;
}