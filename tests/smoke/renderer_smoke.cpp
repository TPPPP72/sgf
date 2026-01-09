#include <sgf/base/texture.hpp>

using namespace sgf::base;

void renderer_smoke_test()
{
    window_info info;
    info.title  = "test";
    info.height = 100;
    info.height = 100;

    window win{info};

    renderer rd{win};
}