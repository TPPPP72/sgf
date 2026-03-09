add_executable(ui_system)

target_compile_features(ui_system PRIVATE cxx_std_17)

target_sources(ui_system
  PRIVATE
    main.cpp
)

target_link_libraries(ui_system
  PRIVATE
    sgf::sgf
)