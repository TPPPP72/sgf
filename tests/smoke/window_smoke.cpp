#include <sgf/base/window/window.hpp>

using namespace sgf::base;

void window_smoke_test()
{
    window_info info;
    info.title  = "test";
    info.height = 100;
    info.height = 100;

    window win{info};
}