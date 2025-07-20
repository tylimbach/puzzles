add_executable(multiply_strings_test 43_multiply_strings_test.cpp)
target_link_libraries(multiply_strings_test
    PRIVATE
        leetcode
        test_main
        gtest
        gmock
)

add_test(NAME MultiplyStringsTest COMMAND multiply_strings_test)