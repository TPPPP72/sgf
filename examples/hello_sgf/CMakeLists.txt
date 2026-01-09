add_executable(hello_sgf)

target_compile_features(hello_sgf PRIVATE cxx_std_17)

target_sources(hello_sgf
  PRIVATE
    hello_sgf.cpp
)

target_link_libraries(hello_sgf
  PRIVATE
    sgf::sgf
)

sgf_copy_runtime_deps(hello_sgf)