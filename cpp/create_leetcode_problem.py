#!/usr/bin/env python3
"""
Script to create a new LeetCode problem solution template.
Usage: python create_leetcode_problem.py <problem_number> <problem_name>
Example: python create_leetcode_problem.py 1 two-sum
"""

import os
import sys
import re
from pathlib import Path

def snake_case(text):
    # Replace hyphens with underscores and convert to lowercase
    return text.replace('-', '_').lower()

def create_header(problem_number, problem_name, snake_name):
    return f'''#pragma once
#include <string>

/*
Problem: {problem_number}. {problem_name.replace('-', ' ').title()}
Difficulty: Medium

TODO: Add problem description here

Example 1:
Input: 
Output: 

Example 2:
Input: 
Output: 

Constraints:

*/

namespace leetcode {{

// TODO: Replace with the actual function signature
int {snake_name}(int input);

}} // namespace leetcode'''

def create_implementation(problem_number, problem_name, snake_name):
    return f'''#include "{problem_number}_{snake_name}.h"

namespace leetcode {{

// TODO: Replace with the actual implementation
int {snake_name}(int input) {{
    // Implementation here
    return 0;
}}

}} // namespace leetcode'''

def create_test(problem_number, problem_name, snake_name):
    return f'''#include <gtest/gtest.h>
#include "../../src/leetcode/{problem_number}_{snake_name}.h"

TEST({problem_name.replace('-', '').title()}Test, Example1) {{
    // TODO: Replace with actual test
    EXPECT_EQ(leetcode::{snake_name}(0), 0);
}}

TEST({problem_name.replace('-', '').title()}Test, Example2) {{
    // TODO: Replace with actual test
    EXPECT_EQ(leetcode::{snake_name}(0), 0);
}}'''

def update_cmake(problem_number, snake_name):
    # Update src/leetcode/CMakeLists.txt
    cmake_path = Path('src/leetcode/CMakeLists.txt')
    with open(cmake_path, 'r') as f:
        content = f.read()
    
    # Find the add_library line
    library_line = re.search(r'add_library\(leetcode\s+([^)]+)\)', content, re.DOTALL)
    if library_line:
        files = library_line.group(1).strip().split('\n')
        files.append(f'    {problem_number}_{snake_name}.cpp')
        files.sort()  # Keep files in order
        new_files = '\n'.join(files)
        updated_content = content.replace(library_line.group(1), new_files)
        
        with open(cmake_path, 'w') as f:
            f.write(updated_content)
    
    # Update tests/leetcode/CMakeLists.txt
    test_cmake_path = Path('tests/leetcode/CMakeLists.txt')
    with open(test_cmake_path, 'r') as f:
        content = f.readlines()
    
    # Add new executable before the last one
    new_executable = f'''add_executable({snake_name}_test {problem_number}_{snake_name}_test.cpp)
target_link_libraries({snake_name}_test
    PRIVATE
        leetcode
        test_main
        gtest
        gmock
)

add_test(NAME {problem_name.replace('-', '').title()}Test COMMAND {snake_name}_test)

'''
    
    # Insert at the end
    content.append(new_executable)
    
    with open(test_cmake_path, 'w') as f:
        f.writelines(content)

def main():
    if len(sys.argv) < 3:
        print("Usage: python create_leetcode_problem.py <problem_number> <problem_name>")
        print("Example: python create_leetcode_problem.py 1 two-sum")
        return
    
    problem_number = sys.argv[1]
    problem_name = sys.argv[2]
    snake_name = snake_case(problem_name)
    
    # Create the header file
    header_path = Path(f'src/leetcode/{problem_number}_{snake_name}.h')
    with open(header_path, 'w') as f:
        f.write(create_header(problem_number, problem_name, snake_name))
    
    # Create the implementation file
    impl_path = Path(f'src/leetcode/{problem_number}_{snake_name}.cpp')
    with open(impl_path, 'w') as f:
        f.write(create_implementation(problem_number, problem_name, snake_name))
    
    # Create the test file
    test_path = Path(f'tests/leetcode/{problem_number}_{snake_name}_test.cpp')
    with open(test_path, 'w') as f:
        f.write(create_test(problem_number, problem_name, snake_name))
    
    # Update CMake files
    update_cmake(problem_number, snake_name)
    
    print(f"Created files for problem {problem_number}: {problem_name}")
    print(f"- {header_path}")
    print(f"- {impl_path}")
    print(f"- {test_path}")
    print("Updated CMake files")

if __name__ == "__main__":
    main()