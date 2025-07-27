cmake_minimum_required(VERSION 3.14)

add_library(io INTERFACE)

target_include_directories(leetcode
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
