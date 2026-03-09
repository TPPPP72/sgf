#include <sgf/sgf.hpp>

inline std::string get_default_font() noexcept
{
#ifdef _WIN32
    return "C:/Windows/Fonts/msyh.ttc";
#elif defined(__APPLE__)
    return "/System/Library/Fonts/PingFang.ttc";
#else
    return "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
#endif
}

class hello_sgf : public sgf::kernel<hello_sgf>
{
public:
    hello_sgf()
        : kernel("hello sgf", {500, 500}, {500, 500}, 0),
          p_font(get_default_font(), 24),
          English(get_renderer(), p_font, "Hello sgf", sgf::type::color::white),
          Chinese(get_renderer(), p_font, "你好sgf", sgf::type::color::blue),
          Japanese(get_renderer(), p_font, "こんにちはsgf", sgf::type::color::red),
          French(get_renderer(), p_font, "Bonjour sgf", sgf::type::color::green),
          Spanish(get_renderer(), p_font, "Hola sgf", sgf::type::color{0, 255, 255, 255})
    {
    }

    void on_input(kernel<hello_sgf> &k, const sgf::input_event &e)
    {
    }

    void on_update(kernel<hello_sgf> &k, const sgf::frame_context &ctx)
    {
        k.get_window().set_title("hello sgf | FPS : " + std::to_string(k.get_current_fps()));
    }

    void on_render(kernel<hello_sgf> &k)
    {
        auto &rd = k.get_renderer();

        rd.render_texture(English, sgf::type::view_position{190, 140});
        rd.render_texture(Chinese, sgf::type::view_position{200, 180});
        rd.render_texture(Japanese, sgf::type::view_position{160, 220});
        rd.render_texture(French, sgf::type::view_position{180, 260});
        rd.render_texture(Spanish, sgf::type::view_position{195, 300});
    }

private:
    sgf::base::font p_font;
    sgf::base::texture English, Chinese, Japanese, French, Spanish;
};

int main()
{
    hello_sgf{}.run();
}