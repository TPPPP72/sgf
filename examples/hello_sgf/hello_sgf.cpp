#include "../get_default_font.hpp"
#include <sgf/base/renderer.hpp>
#include <sgf/base/texture.hpp>
#include <sgf/base/window/window.hpp>

using namespace sgf::base;
using namespace sgf::type;

int main()
{
    window_info init_info;
    init_info.title  = "hello_sgf";
    init_info.width  = 500;
    init_info.height = 500;

    window test_window{init_info};
    renderer test_renderer{test_window};
    font test_font{get_default_font(), 24};
    viewport test_viewport{test_window};
    test_window.on_resize([&test_viewport]()
                          {
                              test_viewport.update();
                          });

    while (true)
    {
        test_renderer.begin_frame(test_viewport);
        test_renderer.clear();
        test_window.poll_event();

        test_renderer.render_texture(texture{test_renderer, test_font, "Hello sgf", color::white}, view_position{190, 140});
        test_renderer.render_texture(texture{test_renderer, test_font, "你好sgf", color::blue}, view_position{200, 180});
        test_renderer.render_texture(texture{test_renderer, test_font, "こんにちはsgf", color::red}, view_position{160, 220});
        test_renderer.render_texture(texture{test_renderer, test_font, "Bonjour sgf", color::green}, view_position{180, 260});
        test_renderer.render_texture(texture{test_renderer, test_font, "Hola sgf", color{0, 255, 255, 255}}, view_position{195, 300});

        test_renderer.present();
        test_renderer.end_frame();
    }
}