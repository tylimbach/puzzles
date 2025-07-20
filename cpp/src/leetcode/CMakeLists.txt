add_library(leetcode
    43_multiply_strings.cpp
)

target_include_directories(leetcode
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)