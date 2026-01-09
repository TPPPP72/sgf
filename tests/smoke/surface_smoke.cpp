#include <sgf/base/surface.hpp>

using namespace sgf::base;

void surface_smoke_test()
{
    font f{"null", 20};
    surface surf{f, "test", sgf::type::color::white};
}