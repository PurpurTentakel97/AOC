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
	print(PrintType::INFO, "day one called");
	print(PrintType::INFO, "first riddle:");

	auto const input{ load("input\\input_1_1.txt") };
	auto count{ 0 };
	auto pos{ 0 };
	auto found{ false };

	for (auto const& c : input) {
		if (std::isspace(c)) { continue; }
		if (not operation.contains(c)) {
			print(PrintType::ERROR, "unexpected character: " + c);
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

	print(PrintType::RESULT, "final count: " + std::to_string(count));
	print(PrintType::RESULT, "first position smaller than 0: " + std::to_string(pos));
}
