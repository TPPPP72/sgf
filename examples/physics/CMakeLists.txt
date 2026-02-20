add_executable(physics)

target_compile_features(physics PRIVATE cxx_std_17)

target_sources(physics
  PRIVATE
    main.cpp
)

target_link_libraries(physics
  PRIVATE
    sgf::sgf
)