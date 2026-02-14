add_executable(scene_switch)

target_compile_features(scene_switch PRIVATE cxx_std_17)

target_sources(scene_switch
  PRIVATE
    main.cpp
)

target_link_libraries(scene_switch
  PRIVATE
    sgf::sgf
)

sgf_copy_runtime_deps(scene_switch)