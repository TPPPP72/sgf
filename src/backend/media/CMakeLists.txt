if(SGF_BACKEND_MEDIA STREQUAL "SDL")
  add_subdirectory(SDL_impl)
  set_property(GLOBAL APPEND PROPERTY SGF_OBJECT_TARGETS
    sgf_backend_media_sdl
  )
endif()