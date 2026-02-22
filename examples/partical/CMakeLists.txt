add_executable(partical)

target_compile_features(partical PRIVATE cxx_std_17)

target_sources(partical
  PRIVATE
    main.cpp
)

target_link_libraries(partical
  PRIVATE
    sgf::sgf
)