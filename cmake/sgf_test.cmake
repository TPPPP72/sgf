include_guard(GLOBAL)

function(sgf_add_test target)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs SOURCES)

  cmake_parse_arguments(SGF_TEST
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
  )

  if (NOT SGF_TEST_SOURCES)
    message(FATAL_ERROR "sgf_add_test(${target}) requires SOURCES")
  endif()

  add_executable(${target})
  target_sources(${target} PRIVATE ${SGF_TEST_SOURCES})

  target_link_libraries(${target}
    PRIVATE
      sgf::sgf
  )

  target_compile_features(${target} PRIVATE cxx_std_17)
  target_compile_definitions(${target} PRIVATE SGF_TEST)

  add_test(
    NAME ${target}
    COMMAND ${target}
  )

  include(sgf_runtime)
  sgf_copy_runtime_deps(${target})
endfunction()