add_executable(particle_system)

target_compile_features(particle_system PRIVATE cxx_std_17)

target_sources(particle_system
  PRIVATE
    main.cpp
)

target_link_libraries(particle_system
  PRIVATE
    sgf::sgf
)