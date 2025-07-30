/*
Tested with M4 Max MBP
L1d - 64/128 KiB eff/perf cores
L1i - 128/192 KiB eff/perf cores
L2 - 4/32 MiB eff/perf cores
*/

#include <benchmark/benchmark.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>

constexpr size_t KB = 1024;
constexpr size_t MB = 1024 * KB;
constexpr size_t GB = 1024 * MB;

constexpr size_t ITERS = 1 * GB;

std::vector<size_t> createPointerChasingBuffer(size_t num_elements) {
    std::vector<size_t> buffer(num_elements);
    std::vector<size_t> indices(num_elements);
    for (size_t i = 0; i < num_elements; ++i) {
        indices[i] = i;
    }

    // Shuffle indices to create a random access pattern
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    // Create the pointer-chasing buffer
    for (size_t i = 0; i < num_elements; ++i) {
        buffer[indices[i]] = indices[(i + 1) % num_elements];
    }

    return buffer;
}

static void Benchmark_CacheThroughput(benchmark::State& state) {
    size_t cache_size = state.range(0);
    size_t num_elements = cache_size / sizeof(size_t);
    auto buffer = createPointerChasingBuffer(num_elements);

    for (auto _ : state) {
        size_t index = 0;
        for (size_t i = 0; i < ITERS; ++i) { // Ensure the same number of accesses
            index = buffer[index];
            benchmark::DoNotOptimize(index);
        }
    }
}

BENCHMARK(Benchmark_CacheThroughput)->Arg(8 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(16 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(32 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(64 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(128 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(256 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(512 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(1024 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(2 * 1024 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(4 * 1024 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(8 * 1024 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(16 * 1024 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(32 * 1024 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(64 * 1024 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(128 * 1024 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(256 * 1024 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(512 * 1024 * KB);
BENCHMARK(Benchmark_CacheThroughput)->Arg(1024 * 1024 * KB);

BENCHMARK_MAIN();
