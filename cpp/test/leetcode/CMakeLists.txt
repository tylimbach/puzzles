add_executable(
    leetcode_tests
    43_multiply_strings_test.cpp
    16_3sum_closest_test.cpp
	js_mock_test.cpp
)

target_link_libraries(leetcode_tests
    PRIVATE
        leetcode
        test_main
        gtest
        gmock
)

add_test(NAME MultiplyStringsTest COMMAND leetcode_tests --gtest_filter=*MultiplyStrings*)
add_test(NAME ThreeSumClosestTest COMMAND leetcode_tests --gtest_filter=*ThreeSumClosest*)
add_test(NAME JsMockTest COMMAND leetcode_tests --gtest_filter=*JsMock*)
