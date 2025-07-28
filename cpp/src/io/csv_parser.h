#pragma once

#include <charconv>
#include <iostream>
#include <istream>
#include <span>
#include <string_view>
#include <unistd.h>
#include <utility>

#include "../util/logger.h"

namespace dev {

template<typename Item, typename... Fields>
concept CsvReadable = requires(Fields... args) {
    { Item(args...) } -> std::convertible_to<Item>;
};

template <typename T, typename... Fields>
	requires CsvReadable<T, Fields...>
class CsvParser {
public:
	CsvParser(std::istream& istream) : istream_(istream) {
		line_buf_.reserve(MAX_LINE_LENGTH);
	}
	bool has_next();
	std::optional<T> read_next();
	size_t read_batch(std::span<T> destination);

private:
	std::istream& istream_;
	std::string line_buf_; 

	static constexpr size_t MAX_LINE_LENGTH = 1000;
	static constexpr char DELIMITER = ',';
	
	template <typename F>
	bool parse_field(std::string_view& sv, F& value);
};

template <typename T, typename... Fields>
	requires CsvReadable<T, Fields...>
std::optional<T> CsvParser<T, Fields...>::read_next() {
	if (!std::getline(istream_, line_buf_)) {
		dev::Logger::info("Failed to get line");
		return {};
	}

	std::string_view sv(line_buf_);
	std::tuple<Fields...> fields;

	dev::Logger::info("Raw line: {}", sv);

	bool success = [&]<size_t... Is>(std::index_sequence<Is...>) {
		return (parse_field(sv, std::get<Is>(fields)) && ...);
	}(std::index_sequence_for<Fields...>{});

	if (!success) {
		dev::Logger::error("Failed to parse line");
		return {};
	}

	return std::apply([](auto&&... args) -> T {
		return T(std::forward<decltype(args)>(args)...);
	}, fields);
}

template <typename T, typename... Fields>
	requires CsvReadable<T, Fields...>
size_t CsvParser<T, Fields...>::read_batch(std::span<T> destination) {
	size_t i;
	for (i = 0; i < destination.size(); i++) {
		auto item = read_next();
		if (item.has_value()) {
			destination[i] = item.value();
		} else {
			return i;
		}
	}

	return i;
}

template <typename T, typename... Fields>
	requires CsvReadable<T, Fields...>
template <typename Field>
bool CsvParser<T, Fields...>::parse_field(std::string_view& sv, Field& value) {
	size_t delimiter_index = sv.find(DELIMITER);
	std::string_view field_sv = delimiter_index != std::string_view::npos
		? sv.substr(0, delimiter_index) 
		: sv;

	dev::Logger::info("About to parse field: {}", field_sv);

    if constexpr (std::is_same_v<Field, double> || std::is_same_v<Field, float>) {
        // For floating point, use string conversion instead of from_chars
        try {
            value = std::stod(std::string(field_sv));
        } catch (const std::exception&) {
			dev::Logger::error("Error parsing floating point type from {}, {}", field_sv, type_name<Field>());
            return false;
        }
    } else if constexpr (std::is_integral_v<Field>) {
        auto result = std::from_chars(field_sv.data(), field_sv.data() + field_sv.size(), value);
        if (result.ec != std::errc{}) {
			dev::Logger::error("Error parsing integral type from {}, {}", field_sv, type_name<Field>());
            return false;
        }
    } else if constexpr (std::is_same_v<Field, std::string>) {
        value = std::string(field_sv);
    }

	dev::Logger::info("Parsed field: {}, {}", value, dev::type_name<Field>());

	if (delimiter_index != std::string_view::npos) {
		sv.remove_prefix(delimiter_index + 1);
	} else {
		sv.remove_prefix(sv.size());
	}

	return true;
}

};

