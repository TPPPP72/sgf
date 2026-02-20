if(SGF_BACKEND_MEDIA STREQUAL "SDL")
  add_subdirectory(SDL_impl)
  set(SGF_ALL_OBJECT_TARGETS ${SGF_ALL_OBJECT_TARGETS} sgf_backend_media_sdl CACHE INTERNAL "")
endif()