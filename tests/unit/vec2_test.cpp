#include <sgf/tool/test.hpp>
#include <sgf/type/vec2.hpp>

using namespace sgf::tool;
using namespace sgf::type;

int main()
{
    vec2d default_vec2;
    test(default_vec2 == vec2d{0, 0}, "default constructor error");
    vec2d a{1.1, 1.1};
    vec2d b{a};
    test(b == a, "copy constructor error");
    vec2d c{std::move(a)};
    test(c == vec2d{1.1, 1.1}, "move constructor error");
    test(vec2d{1.1, 1.1} == vec2d{1.1, 1.1}, "== error");
    test(vec2d{1.1, 1.1} != vec2d{2.2, 2.2}, "!= error");
    test(vec2d{1.1, 1.1} + vec2d{1.1, 1.1} == vec2d{2.2, 2.2}, "vec2 and vec2 + error");
    test(vec2d{1.1, 1.1} + 1.1 == vec2d{2.2, 2.2}, "vec2 and double + error");
    test(vec2d{1.1, 1.1} - vec2d{1.1, 1.1} == vec2d{0.0, 0.0}, "vec2 and vec2 - error");
    test(vec2d{1.1, 1.1} - 1.1 == vec2d{0.0, 0.0}, "vec2 and double - error");
    test(vec2d{2.2, 2.2} * vec2d{2.2, 2.2} == vec2d{4.84, 4.84}, "vec2 and vec2 * error");
    test(vec2d{2.2, 2.2} * 2.2 == vec2d{4.84, 4.84}, "vec2 and double * error");
    test(vec2d{2.2, 2.2} / vec2d{2.2, 2.2} == vec2d{1.0, 1.0}, "vec2 and vec2 / error");
    test(vec2d{2.2, 2.2} / 2 == vec2d{1.1, 1.1}, "vec2 and int / error");
    test(
        []()
        {
            vec2d a{1.1, 1.1};
            a += a;
            return a == vec2d{2.2, 2.2};
        },
        "vec2 and vec2 += error");
    test(
        []()
        {
            vec2d a{1.1, 1.1};
            a += 1.1;
            return a == vec2d{2.2, 2.2};
        },
        "vec2 and double += error");
    test(
        []()
        {
            vec2d a{1.1, 1.1};
            a -= a;
            return a == vec2d{0.0, 0.0};
        },
        "vec2 and vec2 -= error");
    test(
        []()
        {
            vec2d a{1.1, 1.1};
            a -= 1.1;
            return a == vec2d{0.0, 0.0};
        },
        "vec2 and double -= error");
    test(
        []()
        {
            vec2d a{2.2, 2.2};
            a *= a;
            return a == vec2d{4.84, 4.84};
        },
        "vec2 and vec2 *= error");
    test(
        []()
        {
            vec2d a{2.2, 2.2};
            a *= 2.2;
            return a == vec2d{4.84, 4.84};
        },
        "vec2 and double *= error");
    test(
        []()
        {
            vec2d a{2.2, 2.2};
            a /= a;
            return a == vec2d{1.0, 1.0};
        },
        "vec2 and vec2 /= error");
    test(
        []()
        {
            vec2d a{2.2, 2.2};
            a /= 2.2;
            return a == vec2d{1.0, 1.0};
        },
        "vec2 and double /= error");
    a = {1, 1};
    test(a == vec2d{1.0, 1.0}, "vec2 and vec2 == error");

    return test_summary("vec2");
}
