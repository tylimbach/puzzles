cmake_minimum_required(VERSION 3.14)

add_library(leetcode INTERFACE)
target_sources(leetcode
	INTERFACE
        js_mock.h
		43_multiply_strings.h
        16_3sum_closest.h
)

target_include_directories(leetcode
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(leetcode
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
