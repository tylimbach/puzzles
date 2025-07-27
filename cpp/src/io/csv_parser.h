#pragma once

#include <charconv>
#include <iostream>
#include <istream>
#include <span>
#include <string_view>

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
	std::optional<size_t> read_batch(std::span<T> destination);

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
	std::string line;
	std::getline(istream_, line);
}

template <typename T, typename... Fields>
	requires CsvReadable<T, Fields...>
template <typename F>
bool CsvParser<T, Fields...>::parse_field(std::string_view& sv, F& value) {
	size_t delimiter_index = sv.find(DELIMITER);
	std::string_view field = (delimiter_index != std::string_view::npos) ? sv.substr(0, delimiter_index) : sv;

	if constexpr (std::is_arithmetic_v<T>) {
		auto result = std::from_chars(field.data(), field.data() + field.size(), value);
		if (result.ec) {
			return false;
		}
	} else if constexpr (std::is_same_v<T, std::string>) {
		value = std::string(field);
	}

	if (delimiter_index != std::string_view::npos) {
		sv.remove_prefix(delimiter_index + 1);
	} else {
		sv.remove_prefix(sv.size());
	}
}

};

