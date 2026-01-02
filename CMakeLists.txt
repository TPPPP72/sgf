cmake_minimum_required(VERSION 3.25)
project(sgf)

add_subdirectory(src)

add_library(sgf INTERFACE)

target_compile_features(sgf INTERFACE cxx_std_17)

target_include_directories(sgf
  INTERFACE
    include
)

target_link_libraries(sgf
  INTERFACE
    framework_base
)

add_subdirectory(example)