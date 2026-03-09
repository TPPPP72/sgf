add_executable(physics_system)

target_compile_features(physics_system PRIVATE cxx_std_17)

target_sources(physics_system
  PRIVATE
    main.cpp
)

target_link_libraries(physics_system
  PRIVATE
    sgf::sgf
)