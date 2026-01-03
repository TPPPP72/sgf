add_subdirectory(base)

add_library(framework STATIC)

target_compile_features(framework PRIVATE cxx_std_17)

target_sources(framework
  PRIVATE
    input_system.cpp
)