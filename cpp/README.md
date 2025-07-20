# C++ Practice Project

This directory contains C++ implementations and tests for:
- Data structure implementations
- LeetCode problem solutions

## Project Structure

```
cpp/
├── CMakeLists.txt              # Main CMake file
├── include/                    # Common header files
├── src/                        # Source files
│   ├── data_structures/        # Data structure implementations
│   └── leetcode/               # LeetCode solutions
└── tests/                      # Test directory
```

## Building and Testing

### Prerequisites

- CMake 3.14 or higher
- A C++17 compatible compiler

### Build Instructions

1. Create a build directory:
   ```
   mkdir -p build && cd build
   ```

2. Configure with CMake:
   ```
   cmake ..
   ```

3. Build:
   ```
   cmake --build .
   ```

4. Run tests:
   ```
   ctest
   ```

## Adding a New LeetCode Problem

Use the provided script to create a new LeetCode problem solution:

```
python create_leetcode_problem.py <problem_number> <problem_name>
```

Example:
```
python create_leetcode_problem.py 1 two-sum
```

This will:
1. Create header and implementation files in `src/leetcode/`
2. Create a test file in `tests/leetcode/`
3. Update CMake files to include the new problem

## Creating a Custom Data Structure

1. Create header/implementation files in `src/data_structures/`
2. Create test files in `tests/data_structures/`
3. Update the corresponding CMakeLists.txt files