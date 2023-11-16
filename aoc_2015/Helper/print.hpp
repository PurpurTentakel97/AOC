//
// Purpur Tentakel
// AOC 2015
//

#pragma once

#include <string>

namespace hlp {
	enum class PrintType {
		DEBUG,
		INFO,
		ERROR,
		RESULT,
		CALL,
		INPUT,
		QUIT,
		NONE,
	};

	[[nodiscard]] std::string type_to_string(PrintType type);

	void print(PrintType type, std::string const& message);

	void print_day(int n);

	void print_whitespace_ignore();

	void print_unexcepted_character(char c);
}
