#include <iostream>

extern void window_smoke_test();
extern void texture_smoke_test();
extern void renderer_smoke_test();
extern void mixer_smoke_test();
extern void track_smoke_test();

extern void font_smoke_test();
extern void surface_smoke_test();
extern void audio_smoke_test();

#define EXPECT_NO_THROW(x)             \
    try                                \
    {                                  \
        x();                           \
    }                                  \
    catch (const std::exception &e)    \
    {                                  \
        std::cerr << e.what() << '\n'; \
        return 1;                      \
    }

#define EXPECT_THROW(x)                   \
    try                                   \
    {                                     \
        x();                              \
        std::cerr << #x << " no throw\n"; \
        return 1;                         \
    }                                     \
    catch (...)                           \
    {                                     \
    }

int main()
{
    EXPECT_NO_THROW(window_smoke_test);
    EXPECT_NO_THROW(texture_smoke_test);
    EXPECT_NO_THROW(renderer_smoke_test);
    EXPECT_NO_THROW(mixer_smoke_test);
    EXPECT_NO_THROW(track_smoke_test);

    EXPECT_THROW(font_smoke_test);
    EXPECT_THROW(surface_smoke_test);
    EXPECT_THROW(audio_smoke_test);
}