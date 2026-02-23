add_executable(ui)

target_compile_features(ui PRIVATE cxx_std_17)

target_sources(ui
  PRIVATE
    main.cpp
)

target_link_libraries(ui
  PRIVATE
    sgf::sgf
)