add_subdirectory(base)

add_library(sgf_core STATIC)

add_library(sgf::core ALIAS sgf_core)

target_compile_features(sgf_core PRIVATE cxx_std_17)

target_include_directories(sgf_core
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_sources(sgf_core
  PRIVATE
    input_system.cpp
)