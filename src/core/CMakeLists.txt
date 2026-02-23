add_library(sgf_core OBJECT)

target_compile_features(sgf_core PRIVATE cxx_std_17)

target_include_directories(sgf_core
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_sources(sgf_core
  PRIVATE
    resources/atlas.cpp
    resources/manager.cpp
    animation/player.cpp
    game_object/game_object_pool.cpp
    game_object/modules/camera_module.cpp
    game_object/modules/render_module.cpp
    game_object/modules/physics_module.cpp
    game_object/modules/event_module.cpp
    render_pipeline/render_pipeline.cpp
)