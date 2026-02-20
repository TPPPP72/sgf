add_executable(pipeline)

target_compile_features(pipeline PRIVATE cxx_std_17)

target_sources(pipeline
  PRIVATE
    main.cpp
)

target_link_libraries(pipeline
  PRIVATE
    sgf::sgf
)