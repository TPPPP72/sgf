if(SGF_BACKEND_MEDIA STREQUAL "SDL")

  # core
  if(EXISTS "${PROJECT_SOURCE_DIR}/third_party/sdl/SDL/CMakeLists.txt")
    add_subdirectory(sdl/SDL EXCLUDE_FROM_ALL)
  else()
    message(FATAL_ERROR "[SGF] SDL submodule not found! Run git submodule update --init --recursive")
  endif()

  # image
  if(EXISTS "${PROJECT_SOURCE_DIR}/third_party/sdl/SDL_image/CMakeLists.txt")
    add_subdirectory(sdl/SDL_image EXCLUDE_FROM_ALL)
  else()
    message(FATAL_ERROR "[SGF] SDL_image submodule not found! Run git submodule update --init --recursive")
  endif()

  # ttf
  if(EXISTS "${PROJECT_SOURCE_DIR}/third_party/sdl/SDL_ttf/CMakeLists.txt")
    add_subdirectory(sdl/SDL_ttf EXCLUDE_FROM_ALL)
  else()
    message(FATAL_ERROR "[SGF] SDL_ttf submodule not found! Run git submodule update --init --recursive")
  endif()

  # mixer
  if(EXISTS "${PROJECT_SOURCE_DIR}/third_party/sdl/SDL_mixer/CMakeLists.txt")
    add_subdirectory(sdl/SDL_mixer EXCLUDE_FROM_ALL)
  else()
    message(FATAL_ERROR "[SGF] SDL_mixer submodule not found! Run git submodule update --init --recursive")
  endif()

endif()

if(SGF_BACKEND_PHYSICS STREQUAL "BOX2D")

  if(EXISTS "${PROJECT_SOURCE_DIR}/third_party/box2d/CMakeLists.txt")
    set(BOX2D_SAMPLES OFF CACHE BOOL "" FORCE)
    set(BOX2D_UNIT_TESTS OFF CACHE BOOL "" FORCE)
    add_subdirectory(box2d EXCLUDE_FROM_ALL)
  else()
    message(FATAL_ERROR "[SGF] Box2D submodule not found! Run git submodule update --init --recursive")
  endif()

endif()