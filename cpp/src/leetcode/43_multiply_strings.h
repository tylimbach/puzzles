#pragma once
#include <string>
#include <vector>

/*
Problem: 43. Multiply Strings
Difficulty: Medium

Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.

Example 1:
Input: num1 = "2", num2 = "3"
Output: "6"

Example 2:
Input: num1 = "123", num2 = "456"
Output: "56088"

Constraints:
1 <= num1.length, num2.length <= 200
num1 and num2 consist of digits only.
Both num1 and num2 do not contain any leading zero, except the number 0 itself.
*/

namespace leetcode {

inline std::string multiply(std::string num1, std::string num2) {
    // Handle edge cases
    if (num1 == "0" || num2 == "0") return "0";
    
    // Initialize result array with zeros
    std::vector<int> result(num1.size() + num2.size(), 0);
    
    // Multiply each digit and add to result
    for (int i = num1.size() - 1; i >= 0; i--) {
        for (int j = num2.size() - 1; j >= 0; j--) {
            int product = (num1[i] - '0') * (num2[j] - '0');
            int pos1 = i + j;
            int pos2 = i + j + 1;
            
            int sum = product + result[pos2];
            
            result[pos1] += sum / 10;
            result[pos2] = sum % 10;
        }
    }
    
    // Convert to string and remove leading zeros
    std::string resultStr;
    for (int digit : result) {
        if (!(resultStr.empty() && digit == 0)) {
            resultStr.push_back(digit + '0');
        }
    }
    
    return resultStr.empty() ? "0" : resultStr;
}

} // namespace leetcode
