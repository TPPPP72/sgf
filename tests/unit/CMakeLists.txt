include(sgf_test)

message(STATUS "Configuring unit tests...")

file(GLOB TEST_SOURCES *.cpp)

foreach(src ${TEST_SOURCES})
    get_filename_component(name ${src} NAME_WE)
    sgf_add_test(
        ${name}
        SOURCES ${src}
    )
endforeach()

message(STATUS "[SGF] Unit tests configuration successed!")