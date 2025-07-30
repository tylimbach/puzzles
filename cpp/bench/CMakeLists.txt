cmake_minimum_required(VERSION 3.14)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.4
)
FetchContent_MakeAvailable(googletest googlebenchmark)

add_executable(csv_parser_benchmark csv_parser_benchmark.cpp)
target_link_libraries(csv_parser_benchmark PRIVATE benchmark::benchmark_main io)

add_executable(cpu_cache_benchmark cpu_cache_benchmark.cpp)
target_link_libraries(cpu_cache_benchmark PRIVATE benchmark::benchmark_main)
