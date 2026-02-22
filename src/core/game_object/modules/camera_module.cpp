#include <algorithm>
#include <sgf/camera/camera.hpp>
#include <sgf/context/scene_context.hpp>
#include <sgf/game_object/modules/camera_module.hpp>
#include <sgf/scene/scene.hpp>

sgf::camera *sgf::module::camera_module::get_by_tag(std::string_view tag) const
{
    auto &cameras = this->context().cameras;

    auto it = std::find_if(cameras.begin(), cameras.end(), [tag](const auto &cam)
                           {
                               if (cam->tag() == tag)
                                   return true;
                               return false;
                           });

    if (it != cameras.end())
        return *it;

    return nullptr;
}

sgf::camera *sgf::module::camera_module::get_main() const
{
    return get_by_tag("main");
}