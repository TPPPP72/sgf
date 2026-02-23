add_library(sgf_backend_media_sdl OBJECT)

target_compile_features(sgf_backend_media_sdl PRIVATE cxx_std_17)

target_include_directories(sgf_backend_media_sdl
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_sources(sgf_backend_media_sdl
  PRIVATE
    window.cpp
    renderer.cpp
    texture.cpp
    font.cpp
    surface.cpp
    mixer.cpp
    track.cpp
    audio.cpp
    video_system.cpp
    audio_system.cpp
    font_system.cpp
)

target_link_libraries(sgf_backend_media_sdl
  PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
)