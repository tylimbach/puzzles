#include <benchmark/benchmark.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <span>
#include "../../src/io/csv_parser.h"

struct LoMidHiCt {
    double low;
    double mid;
    double high;
    int count;

    auto operator<=>(const LoMidHiCt&) const = default;
};

static void Benchmark_ReadSingleRow(benchmark::State& state) {
    const std::string file_path = "../res/large_csv_lomidhict.csv";

    for (auto _ : state) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            state.SkipWithError("Failed to open CSV file");
            return;
        }

        dev::CsvParser<LoMidHiCt, double, double, double, int> parser(file);
		while (std::optional<LoMidHiCt> row = parser.read_next()) {
			benchmark::DoNotOptimize(row);
			continue;
		}
    }
}

static void Benchmark_ReadBatchRows(benchmark::State& state) {
    const std::string file_path = "../res/large_csv_lomidhict.csv";

    for (auto _ : state) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            state.SkipWithError("Failed to open CSV file");
            return;
        }

        std::vector<LoMidHiCt> items(100000);
        std::span<LoMidHiCt> view(items);
        dev::CsvParser<LoMidHiCt, double, double, double, int> parser(file);

		while (size_t lines_read = parser.read_batch(view)) {
			benchmark::DoNotOptimize(lines_read);
			continue;
		}
        benchmark::DoNotOptimize(items);
    }
}

BENCHMARK(Benchmark_ReadSingleRow);
BENCHMARK(Benchmark_ReadBatchRows);

BENCHMARK_MAIN();
