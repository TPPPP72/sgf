#include <sgf/base/viewport.hpp>
#include <sgf/tool/test.hpp>

using namespace sgf::tool;
using namespace sgf;

int main()
{
    base::viewport vp({1920, 1080}, {1280, 720});
    vp.update();

    test(vp.get_scale() == 1.5, "scale should be 1.5");

    auto offset = vp.get_offset();
    test(offset.x == 0 && offset.y == 0, "offset should be (0,0)");

    type::view_position vpos{640, 360};
    auto wpos  = vp.to_window_position(vpos);
    auto vpos2 = vp.to_view_position(wpos);
    test(vpos.x == vpos2.x && vpos.y == vpos2.y, "roundtrip view->window->view error");

    type::view_rect vr{0, 0, 1280, 720};
    auto wr  = vp.to_window_rect(vr);
    auto vr2 = vp.to_view_rect(wr);
    test(vr.x == vr2.x && vr.y == vr2.y &&
             vr.w == vr2.w && vr.h == vr2.h,
         "rect roundtrip error");

    return test_summary("viewport");
}