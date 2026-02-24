include_guard(GLOBAL)

if(WIN32 AND NOT MSVC)
    message(WARNING "[SGF] Platform is Windows, but the compiler is NOT MSVC. "
                    "Current compiler: ${CMAKE_CXX_COMPILER_ID}. "
                    "This may lead to compatibility issues with system APIs.")
endif()

if(APPLE)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(WARNING "[SGF] Platform is Apple, but the compiler is NOT Clang. "
                        "Current compiler: ${CMAKE_CXX_COMPILER_ID}. "
                        "Official SDKs and frameworks expect Clang.")
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(WARNING "[SGF] Platform is Linux, but the compiler is NOT GCC. "
                        "Current compiler: ${CMAKE_CXX_COMPILER_ID}. "
                        "GCC is the recommended compiler for this project on Linux.")
    endif()
endif()