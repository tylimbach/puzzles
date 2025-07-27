/*
Jane Street Mock Interview Video
https://www.youtube.com/watch?v=V8DGdPkBBxg&t=308s

Unit conversion
*/

#pragma once

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace leetcode {
namespace js {

struct Fact {
	std::string in_unit;
	double ratio; // ratio = Out / In
	std::string out_unit;
};

struct Query {
	double magnitude;
	std::string in_unit;
	std::string out_unit;
};

struct Conversion {
	std::string in_unit;
	std::string out_unit;

    auto operator<=>(const Conversion&) const = default;

    struct Hash {
        size_t operator()(const Conversion& c) const {
            size_t h1 = std::hash<std::string>{}(c.in_unit);
            size_t h2 = std::hash<std::string>{}(c.out_unit);
            return h1 ^ (h2 << 1);
        }
    };
};

struct ConversionNode {
	std::string unit;
	double ratio;	
};

std::unordered_map<std::string, std::vector<ConversionNode>> build_conversion_graph(const std::vector<Fact>& facts) {
	std::unordered_map<std::string, std::vector<ConversionNode>> conversion_graph{};

	for (Fact fact : facts) {
		auto [it, inserted] = conversion_graph.try_emplace(fact.in_unit, ConversionNode { fact.out_unit, fact.ratio });
		auto [it_rev, inserted_rev] = conversion_graph.try_emplace(fact.out_unit, ConversionNode { fact.in_unit, 1 / fact.ratio });
		if (!inserted) {
			it->second.push_back({ fact.out_unit, fact.ratio });
		}
		if (!inserted_rev) {
			it_rev->second.push_back({ fact.in_unit, 1 / fact.ratio });
		}
	}

	return conversion_graph;
}

std::optional<double> dfs(
	const std::unordered_map<std::string, std::vector<ConversionNode>>& conversion_graph, 
	std::set<std::string>& seen_units, 
	double value,
	std::string& current_unit,
	std::string& output_unit
) {
	auto [_, inserted] = seen_units.emplace(current_unit);
	if (!inserted || !conversion_graph.contains(current_unit)) {
		return {};
	}

	if (current_unit == output_unit) {
		return value;
	}

	auto& nodes = conversion_graph.at(current_unit);
	for (ConversionNode node : nodes) {
		auto option = dfs(conversion_graph, seen_units, value * node.ratio, node.unit, output_unit);
		if (option.has_value()) {
			return option.value();
		}
	}

	return {};
}

std::vector<std::optional<double>> query(const std::vector<Fact>& facts, const std::vector<Query>& queries) {
	auto conversion_map = build_conversion_graph(facts);
	std::vector<std::optional<double>> results{};
	results.reserve(queries.size());

	std::set<std::string> seen_units {};
	for (Query query : queries)	 {
		for (auto& [key, value] : conversion_map) {
			if (!seen_units.contains(key)) {
				auto option = dfs(conversion_map, seen_units, query.magnitude, query.in_unit, query.out_unit);
				if (option.has_value()) {
					results.push_back(option.value());
				}
			}
		}

		results.push_back({});
	}

	return results;
}

std::unordered_map<Conversion, double, Conversion::Hash> conversion_graph{};
};
};

