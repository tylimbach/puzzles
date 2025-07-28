add_executable(io_test csv_parser_test.cpp)
target_link_libraries(io_test
    PRIVATE
        io
        test_main
        gtest
        gmock
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME IOTest COMMAND io_test)
