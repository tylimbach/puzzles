cmake_minimum_required(VERSION 3.14)
project(cpp_practice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_TESTS "Build the tests" ON)

# Include directories
find_package(Boost 1.88.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Add source directories
add_subdirectory(src)

# Add tests if enabled
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
