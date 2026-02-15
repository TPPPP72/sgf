#include "../get_default_font.hpp"
#include <sgf/base/font.hpp>
#include <sgf/base/texture.hpp>
#include <sgf/kernel.hpp>
#include <sgf/type/color.hpp>
#include <sgf/type/position.hpp>
#include <string>

using namespace sgf;

class hello_sgf : public kernel<hello_sgf>
{
public:
    hello_sgf()
        : kernel("hello sgf", {500, 500}, {500, 500}, 60),
          p_font(get_default_font(), 24),
          English(get_renderer(), p_font, "Hello sgf", type::color::white),
          Chinese(get_renderer(), p_font, "你好sgf", type::color::blue),
          Japanese(get_renderer(), p_font, "こんにちはsgf", type::color::red),
          French(get_renderer(), p_font, "Bonjour sgf", type::color::green),
          Spanish(get_renderer(), p_font, "Hola sgf", type::color{0, 255, 255, 255})
    {
    }

    void on_update(kernel<hello_sgf> &k, std::chrono::nanoseconds dt)
    {
        k.get_window().set_title(+"hello sgf | FPS : " + std::to_string(k.get_current_fps()));
    }

    void on_render(kernel<hello_sgf> &k)
    {
        auto &rd = k.get_renderer();

        rd.render_texture(English, type::view_position{190, 140});
        rd.render_texture(Chinese, type::view_position{200, 180});
        rd.render_texture(Japanese, type::view_position{160, 220});
        rd.render_texture(French, type::view_position{180, 260});
        rd.render_texture(Spanish, type::view_position{195, 300});
    }

private:
    base::font p_font;
    base::texture English, Chinese, Japanese, French, Spanish;
};

int main()
{
    hello_sgf{}.run();
}