if(SGF_BACKEND_PHYSICS STREQUAL "BOX2D")
  add_subdirectory(Box2D_impl)
  set_property(GLOBAL APPEND PROPERTY SGF_OBJECT_TARGETS
    sgf_backend_physics_box2d
  )
endif()