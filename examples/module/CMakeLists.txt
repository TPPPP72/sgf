add_executable(module)

target_compile_features(module PRIVATE cxx_std_17)

target_sources(module
  PRIVATE
    main.cpp
)

target_link_libraries(module
  PRIVATE
    sgf::sgf
)

sgf_copy_runtime_deps(module)