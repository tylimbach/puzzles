#!/bin/bash
# Simple build script for the C++ practice project

set -e  # Exit on error

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure with CMake
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build
cmake --build . -j$(nproc)

# Run tests if requested
if [ "$1" == "test" ]; then
    ctest --verbose
fi
