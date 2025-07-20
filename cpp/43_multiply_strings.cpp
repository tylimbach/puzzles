// https://leetcode.com/problems/multiply-strings/description/
/*
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


#include <iostream>
#include <memory>

using namespace std;
string multiply(string num1, string num2) {
	size_t const len1 = num1.length();
	size_t const len2 = num2.length();

	int mult1 = 1, mult2 = 1;
	for (int i = 1; i < len1; i++) {
		mult1 *= 10;
	}
	for (int i = 1; i < len2; i++) {
		mult2 *= 10;
	}

	long res = 0;
	for (int i = 0; i < len1; i++) {
		int mult2_cpy = mult2;
		long val1 = (num1[i] - '0') * mult1;
		for (int j = 0; j < len2; j++) {	
			long val2 = (num2[j] - '0') * mult2;	
			res += (val1 * val2); 
			mult2 /= 10;
		}
		mult2 = mult2_cpy;
		mult1 /= 10;
	}

	return std::to_string(res);
}

int main() {
	std::cout << multiply("12", "3") << std::endl;
}

