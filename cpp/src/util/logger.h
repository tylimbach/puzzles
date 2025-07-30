#pragma once

#include <string_view>
#include <utility>
#include <iostream>
namespace dev {

enum class LogLevel { DEBUG, INFO, WARN, ERROR };

#ifdef LOGINFO
	constexpr LogLevel MIN_LOG_LEVEL = LogLevel::INFO;
#else
	constexpr LogLevel MIN_LOG_LEVEL = LogLevel::ERROR;
#endif

class Logger {
public:
	template <LogLevel LEVEL, typename... Args>
	static void log(std::format_string<Args...> fmt, Args&&... args) {
		if constexpr (LEVEL >= MIN_LOG_LEVEL) {
			std::cout << levelPrefix(LEVEL)
			          << std::format(fmt, std::forward<Args>(args)...)
				      << std::endl;
		}
	}

	template <typename... Args>
	static void debug(std::format_string<Args...> fmt, Args&&... args) {
		log<LogLevel::DEBUG>(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void info(std::format_string<Args...> fmt, Args&&... args) {
		log<LogLevel::INFO>(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void warn(std::format_string<Args...> fmt, Args&&... args) {
		log<LogLevel::WARN>(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void error(std::format_string<Args...> fmt, Args&&... args) {
		log<LogLevel::ERROR>(fmt, std::forward<Args>(args)...);
	}

private:
	static constexpr const char* levelPrefix(LogLevel level) {
		switch (level) {
			case dev::LogLevel::DEBUG: return "[DEBUG] ";
			case dev::LogLevel::INFO: return "[INFO]  ";
			case dev::LogLevel::WARN: return "[WARN]  ";
			case dev::LogLevel::ERROR: return "[ERROR] ";
		}

		return "";
	}
};


template <typename T>
constexpr std::string_view type_name() {
#if defined(__clang__)
	constexpr std::string_view p = __PRETTY_FUNCTION__;
	constexpr std::string_view prefix = "std::string_view type_name() [with T = "; // this may be wrong but len seems correct
	constexpr std::string_view suffix = "]";
	return p.substr(prefix.size(), p.size() - prefix.size() - suffix.size());
#elif defined(__GNUC__)
	constexpr std::string_view p = __PRETTY_FUNCTION__;
	constexpr std::string_view prefix = "constexpr std::string_view type_name() [with T = ";
	constexpr std::string_view suffix = "]";
	return p.substr(prefix.size(), p.size() - prefix.size() - suffix.size());
#elif defined(_MSC_VER)
	constexpr std::string_view p = __FUNCSIG__;
	constexpr std::string_view prefix = "class std::basic_string_view<char,struct std::char_traits<char> > __cdecl type_name<";
	constexpr std::string_view suffix = ">(void)";
	return p.substr(prefix.size(), p.size() - prefix.size() - suffix.size());
#else
	return "unsupported compiler";
#endif
}

}
