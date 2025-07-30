add_executable(io_test csv_parser_test.cpp)
target_link_libraries(io_test
    PRIVATE
        io
        test_main
        gtest
        gmock
)

add_test(NAME IOTest COMMAND io_test)
