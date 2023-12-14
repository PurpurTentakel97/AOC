//
// Purpur Tentakel
// AOC helper
//

#pragma once

#include <vector>
#include <string>

namespace hlp {
	[[nodiscard]] std::vector<std::string> split(std::stringstream entry, char delimiter);

    [[nodiscard]] std::string flip(std::string s);

    [[nodiscard]] bool is_multiple_digit(std::string const& s);

	void ltrim(std::string& s);
	void rtrim(std::string& s);
	void trim (std::string& s);

	[[nodiscard]] std::string ltrim_copy(std::string s);
	[[nodiscard]] std::string rtrim_copy(std::string s);
	[[nodiscard]] std::string trim_copy (std::string s);
}
