add_executable(event_bus)

target_compile_features(event_bus PRIVATE cxx_std_17)

target_sources(event_bus
  PRIVATE
    main.cpp
)

target_link_libraries(event_bus
  PRIVATE
    sgf::sgf
)