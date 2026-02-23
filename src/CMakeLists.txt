add_subdirectory(core)
add_subdirectory(backend)

get_property(SGF_OBJECT_TARGETS GLOBAL PROPERTY SGF_OBJECT_TARGETS)

add_library(sgf_static STATIC)
set_target_properties(sgf_static PROPERTIES OUTPUT_NAME "sgf")
target_compile_features(sgf_static PRIVATE cxx_std_17)

target_include_directories(sgf_static
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_sources(sgf_static
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include/sgf/__clangd__.cpp
)

target_link_libraries(sgf_static
  PRIVATE
    sgf_core
    ${SGF_OBJECT_TARGETS}
)