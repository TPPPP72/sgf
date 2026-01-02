add_executable(example)

target_compile_features(example PRIVATE cxx_std_17)

target_sources(example
  PRIVATE
    main.cpp
)

target_link_libraries(example
  PRIVATE
    sgf
)

if (WIN32)
  add_custom_command(
    TARGET example
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:example>
            $<TARGET_FILE_DIR:example>
    COMMAND_EXPAND_LISTS
  )
endif()