set(SGF_ALL_OBJECT_TARGETS "" CACHE INTERNAL "")

add_subdirectory(core)
add_subdirectory(backend)

set(OBJ_FILES "")
foreach(target ${SGF_ALL_OBJECT_TARGETS})
    list(APPEND OBJ_FILES $<TARGET_OBJECTS:${target}>)
endforeach()

add_library(sgf_static STATIC ${OBJ_FILES})
set_target_properties(sgf_static PROPERTIES OUTPUT_NAME "sgf")

target_link_libraries(sgf_static
    PUBLIC
      sgf_core
    PRIVATE
      ${SGF_ALL_OBJECT_TARGETS}
)