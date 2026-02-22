add_executable(particle)

target_compile_features(particle PRIVATE cxx_std_17)

target_sources(particle
  PRIVATE
    main.cpp
)

target_link_libraries(particle
  PRIVATE
    sgf::sgf
)