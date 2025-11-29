cmake_minimum_required(VERSION 4.0)
project(programming_cpp_2025)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

include_directories(.)

add_executable(programming_cpp_2025
        main.cpp
        SparseVector.cpp)

add_executable(tests
        test.cpp
        SparseVector.cpp)

target_link_libraries(tests gtest_main)
