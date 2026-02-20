if(SGF_BACKEND_PHYSICS STREQUAL "BOX2D")
  add_subdirectory(Box2D_impl)
  set(SGF_ALL_OBJECT_TARGETS ${SGF_ALL_OBJECT_TARGETS} sgf_backend_physics_box2d CACHE INTERNAL "")
endif()