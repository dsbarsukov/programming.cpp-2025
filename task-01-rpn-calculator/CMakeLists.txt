cmake_minimum_required(VERSION 3.14)
project(rpn_calculator)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(rpn_calculator
        main.cpp
        RPNCalculator.cpp
)

add_executable(rpn_calculator_tests
        test.cpp
        RPNCalculator.cpp
)

target_link_libraries(rpn_calculator_tests gtest_main)