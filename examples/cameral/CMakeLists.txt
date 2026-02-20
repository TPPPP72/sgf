add_executable(cameral)

target_compile_features(cameral PRIVATE cxx_std_17)

target_sources(cameral
  PRIVATE
    main.cpp
)

target_link_libraries(cameral
  PRIVATE
    sgf::sgf
)