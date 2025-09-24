add_executable(
    leetcode_tests
    43_multiply_strings_test.cpp
	38_count_and_say_test.cpp
	js_mock_test.cpp
    16_3sum_closest_test.cpp
	97_interleaving_string.cpp
	12_integer_to_roman_test.cpp
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
add_test(NAME CountAndSayTest COMMAND leetcode_tests --gtest_filter=*CountAndSay*)
add_test(NAME InterleavingStringTest COMMAND leetcode_tests --gtest_filter=*InterleavingString*)
add_test(NAME IntegerToRomanTest COMMAND leetcode_tests --gtest_filter=*IntegerToRoman*)
