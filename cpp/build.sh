#!/bin/bash

set -e

mkdir -p build
cd build

BUILD_TYPE="Debug"

for arg in "$@"; do
    if [ "$arg" == "release" ]; then
        BUILD_TYPE="Release"
    elif [ "$arg" == "test" ]; then
        RUN_TESTS=true
    fi
done

cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$BUILD_TYPE

cmake --build . -j$(nproc)

if [ "$RUN_TESTS" == "true" ]; then
    ctest --verbose
fi
