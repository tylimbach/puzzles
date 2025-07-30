cmake_minimum_required(VERSION 3.14)
project(cpp_practice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS_JSON ON)

option(BUILD_TESTS "Build the tests" ON)

find_package(Boost 1.88.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(bench)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
