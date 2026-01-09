add_library(sgf_backend INTERFACE)

add_library(sgf::backend ALIAS sgf_backend)

if(SGF_BACKEND_IMPL STREQUAL "SDL")
  add_subdirectory(SDL_impl)
  target_link_libraries(sgf_backend INTERFACE sgf::backend::sdl)
endif()