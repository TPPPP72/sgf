add_library(sgf_backend_physics_box2d OBJECT)

target_compile_features(sgf_backend_physics_box2d PRIVATE cxx_std_20)

target_include_directories(sgf_backend_physics_box2d
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_sources(sgf_backend_physics_box2d
  PRIVATE
    physics_system.cpp
)

target_link_libraries(sgf_backend_physics_box2d
  PRIVATE
    box2d
)