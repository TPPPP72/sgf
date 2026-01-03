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
    font     test_font{"C:/Windows/Fonts/msyh.ttc", 24};

    while (true)
    {
        test_renderer.clear();
        test_window.poll_event();
        auto event = test_window.current_event();

        std::string keys;
        for (int i = 1; i <= 26; ++i)
        {
            if (event.keys.count(static_cast<key_code>(i + 3)) && event.keys.at(static_cast<key_code>(i + 3)))
                keys += static_cast<char>('A' + i - 1);
        }

        if (keys.empty())
            keys = "empty";
        auto tex = texture{test_renderer, test_font, keys, {255, 255, 255, 255}};
        test_renderer.render_texture(tex, 20, 20);
        test_renderer.present();
    }
}