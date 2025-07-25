cmake_minimum_required(VERSION 3.14)

# Download and configure GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(data_structures)
add_subdirectory(leetcode)

# Configure all tests to have standard main function
add_library(test_main STATIC test_main.cpp)
target_link_libraries(test_main PUBLIC gtest gmock)
