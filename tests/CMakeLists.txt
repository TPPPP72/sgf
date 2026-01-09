add_subdirectory(unit)

if(APPLE OR SGF_TEST_LOCAL)
  add_subdirectory(smoke)
endif()