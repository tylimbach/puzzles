add_executable(
    leetcode_tests
    43_multiply_strings_test.cpp
    16_3sum_closest_test.cpp
)

target_link_libraries(leetcode_tests
    PRIVATE
        leetcode
        test_main
        gtest
        gmock
)

add_test(NAME MultiplyStringsTest COMMAND leetcode_tests --gtest_filter="*MultiplyStrings*")
add_test(NAME 3SumClosestTest COMMAND leetcode_tests --gtest_filter="*3SumClosest*")
