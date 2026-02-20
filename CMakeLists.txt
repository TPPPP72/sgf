cmake_minimum_required(VERSION 3.25)
project(sgf)

set(SGF_BACKEND_MEDIA "SDL" CACHE STRING "Media implementation (SDL3)")
option(SGF_BUILD_EXAMPLES "Build sgf examples" ON)
option(SGF_BUILD_TESTS "Build sgf tests" ON)

if(SGF_BUILD_TESTS)
  option(SGF_TEST_LOCAL "Test on local environment" True)
endif()

if(MSVC)
  add_compile_options(/utf-8)
endif()

add_subdirectory(third_party)

add_subdirectory(src)

add_library(sgf INTERFACE)

add_library(sgf::sgf ALIAS sgf)

target_compile_features(sgf INTERFACE cxx_std_17)

target_include_directories(sgf
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(sgf
  INTERFACE
    sgf_static
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(sgf_runtime)

if(SGF_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(SGF_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()