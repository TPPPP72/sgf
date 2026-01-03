cmake_minimum_required(VERSION 3.25)
project(sgf)

option(SGF_BUILD_EXAMPLES "Build sgf examples" ON)

add_subdirectory(src)

add_library(sgf INTERFACE)

add_library(sgf::sgf ALIAS sgf)

target_compile_features(sgf INTERFACE cxx_std_17)

target_include_directories(sgf
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(sgf
  INTERFACE
    framework_base
    framework
)

if(SGF_BUILD_EXAMPLES)
  add_subdirectory(example)
endif()