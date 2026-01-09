#ifndef SGF_TOOL_TEST_HPP
#define SGF_TOOL_TEST_HPP

#include <cstdint>
#include <iostream>
#include <string_view>
#include <type_traits>
#include <utility>

namespace sgf::tool
{

inline std::int64_t g_test_failed = 0;

template <typename Func, typename... Args>
auto test(const Func &func, std::string_view info, Args &&...args)
    -> std::enable_if_t<std::is_same_v<std::invoke_result_t<Func, Args...>, bool>>
{
    if (!func(std::forward<Args>(args)...))
    {
        std::cerr << "❌ Test failed: " << info << "\n";
        ++g_test_failed;
    }
}

inline void test(bool expect, std::string_view info)
{
    if (!expect)
    {
        std::cerr << "❌ Test failed: " << info << "\n";
        ++g_test_failed;
    }
}

inline std::int32_t test_summary(std::string_view name = "")
{
    if (g_test_failed == 0)
    {
        std::cout << "✅ [" << name << "] All tests passed.\n";
        return 0;
    }
    else
    {
        std::cerr << "❌ [" << name << "] " << g_test_failed << " tests failed.\n";
        return 1;
    }
}

} // namespace sgf::tool

#endif