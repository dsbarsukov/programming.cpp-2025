cmake_minimum_required(VERSION 3.14)
project(sparse_vector)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(sparse_vector
        main.cpp
        SparseVector.cpp)

add_executable(sparse_vector_tests
        test.cpp
        SparseVector.cpp)

target_link_libraries(sparse_vector_tests gtest_main)