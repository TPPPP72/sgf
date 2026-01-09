include(sgf_test)

message(STATUS "Configuring smoke tests...")

file(GLOB TEST_SOURCES *.cpp)

sgf_add_test(
    sgf_smoke_test
    SOURCES ${TEST_SOURCES}
)
message(STATUS "✅ Smoke tests configuration successed!")