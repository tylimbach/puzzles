cmake_minimum_required(VERSION 3.14)

add_library(io INTERFACE)

target_include_directories(io
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)
