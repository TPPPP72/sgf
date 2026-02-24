cmake_minimum_required(VERSION 3.25)
project(sgf)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(SGF_BACKEND_MEDIA "SDL" CACHE STRING "Media implementation (SDL3)")
set(SGF_BACKEND_PHYSICS "BOX2D" CACHE STRING "Physics implementation (BOX2D)")

option(SGF_BUILD_EXAMPLES "Build sgf examples" ON)
option(SGF_BUILD_TESTS "Build sgf tests" ON)

if(SGF_BUILD_TESTS)
  option(SGF_TEST_LOCAL "Test on local environment" True)
endif()

include(sgf_dependencies_helper)

# 如果开启了 CMAKE_EXPORT_COMPILE_COMMANDS，临时关闭，防止第三方库干扰
# if CMAKE_EXPORT_COMPILE_COMMANDS = ON, temporarily close it to avoid third_party's inference 
set(OLD_EXPORT_STATUS ${CMAKE_EXPORT_COMPILE_COMMANDS})
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party)
set(CMAKE_EXPORT_COMPILE_COMMANDS ${OLD_EXPORT_STATUS} CACHE BOOL "" FORCE)

add_subdirectory(src)

add_library(sgf INTERFACE)

add_library(sgf::sgf ALIAS sgf)

target_compile_features(sgf INTERFACE cxx_std_17)

target_link_libraries(sgf
  INTERFACE
    sgf_static
)

if(SGF_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(SGF_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

include(sgf_environment)