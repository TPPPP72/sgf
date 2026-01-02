add_executable(example WIN32)

target_compile_features(example PRIVATE cxx_std_17)

target_sources(example
  PRIVATE
    main.cpp
)

target_link_libraries(example
  PRIVATE
    sgf::sgf
)