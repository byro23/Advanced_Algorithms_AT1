cmake_minimum_required(VERSION 3.28)
project(Advanced_Algorithms_AT1)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/6dae7eb4a5c3a169f3e298392bff4680224aa94a.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        main
        main.cpp
)
target_link_libraries(
        main
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(main)