include_guard(GLOBAL)

function(sgf_copy_runtime_deps target)
  if(NOT WIN32)
    return()
  endif()

  if(NOT TARGET ${target})
    message(FATAL_ERROR "sgf_copy_runtime_deps: target '${target}' does not exist")
  endif()

  if(MSVC)
    add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<$<CONFIG:Debug>:$<TARGET_RUNTIME_DLLS:${target}>>
        $<$<CONFIG:Release>:$<TARGET_RUNTIME_DLLS:${target}>>
        $<TARGET_FILE_DIR:${target}>
      COMMAND_EXPAND_LISTS
    )
  else()
    add_custom_command(
      TARGET ${target}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:${target}>
        $<TARGET_FILE_DIR:${target}>
      COMMAND_EXPAND_LISTS
    )
  endif()
endfunction()