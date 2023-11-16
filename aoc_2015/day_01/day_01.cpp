//
// Purpur Tentakel
// AOC 01/2015
//

#include "day_01.hpp"
#include "print.hpp"
#include "load.hpp"
#include <unordered_map>
#include <cctype>


static constexpr char add{ '(' };
static constexpr char sub{ ')' };
static inline std::unordered_map<char, int> operation{
	{ add,  1 },
	{ sub, -1 },
};

void day_01() {
	hlp::print(hlp::PrintType::INFO, "day one called");

	auto const input{ hlp::load("input\\input_01_1.txt") };
	auto count{ 0 };
	auto pos{ 0 };
	auto found{ false };

	for (auto const& c : input) {
		if (std::isspace(c)) { continue; }
		if (not operation.contains(c)) {
			hlp::print(hlp::PrintType::ERROR, "unexpected character: " + c);
			continue;
		}

		count += operation[c];
		if (not found) {
			++pos;
		}
		if (count < 0) {
			found = true;
		}
	}

	hlp::print(hlp::PrintType::RESULT, "final count: " + std::to_string(count));
	hlp::print(hlp::PrintType::RESULT, "first position smaller than 0: " + std::to_string(pos));
}
