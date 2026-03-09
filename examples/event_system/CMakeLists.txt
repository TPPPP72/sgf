add_executable(event_system)

target_compile_features(event_system PRIVATE cxx_std_17)

target_sources(event_system
  PRIVATE
    main.cpp
)

target_link_libraries(event_system
  PRIVATE
    sgf::sgf
)