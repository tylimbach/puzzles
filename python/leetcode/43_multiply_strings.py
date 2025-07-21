'''
https://leetcode.com/problems/multiply-strings/description/
Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.
'''

def multiply(num1: str, num2: str) -> str:
    digits: list[int] = [0 for _ in range(len(num1) + len(num2))]
    
    for i1, n1 in num1:
        for i2, n2 in num2:
            digits[i1 + i2] += int(n1) * int(n2)
    
    digits2 = []    
    carry = 0
    for digit in digits.reverse():
        