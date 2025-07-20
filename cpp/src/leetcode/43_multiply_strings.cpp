#include "43_multiply_strings.h"
#include <vector>

namespace leetcode {

std::string multiply(std::string num1, std::string num2) {
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