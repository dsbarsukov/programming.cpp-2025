cmake_minimum_required(VERSION 3.14)
project(heap)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(heap main.cpp)

add_executable(heap_tests test.cpp)

target_link_libraries(heap_tests gtest_main)