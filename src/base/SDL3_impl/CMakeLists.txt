add_subdirectory(thirdparty)

add_library(framework_base STATIC)

target_compile_features(framework_base PRIVATE cxx_std_17)

target_sources(framework_base
  PRIVATE
    window.cpp
    renderer.cpp
    texture.cpp
    font.cpp
    surface.cpp
)

target_link_libraries(framework_base
  PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
)