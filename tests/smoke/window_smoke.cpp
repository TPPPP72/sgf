#include <sgf/base/window/window.hpp>

using namespace sgf::base;

void window_smoke_test()
{
    window_info info;
    info.title  = "test";
    info.size.w = 100;
    info.size.h = 100;

    window win{info};
}