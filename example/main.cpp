#include <sgf/base/renderer.hpp>
#include <sgf/base/texture.hpp>
#include <sgf/base/window/window.hpp>

using namespace sgf::base;

int main()
{
    window_info init_info;
    init_info.title  = "test";
    init_info.width  = 500;
    init_info.height = 500;

    window   test_window{init_info};
    renderer test_renderer{test_window};
    font     test_font{"misans.ttf", 24};

    auto hello_world = texture{test_renderer, test_font, "Hello World!", {255, 255, 255, 255}};

    while (true)
    {
        test_renderer.clear();
        test_window.poll_event();
        test_renderer.render_texture(hello_world, 20, 20);
        test_renderer.present();
    }
}