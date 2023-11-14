//
// Purpur Tentakel
// AOC 2015
//

#pragma once

#include <string>

enum class PrintType {
	DEBUG,
	INFO,
	ERROR,
	NONE,
};

[[nodiscard]] std::string const& type_to_string(PrintType type);

void print(PrintType type, std::string const& message);
