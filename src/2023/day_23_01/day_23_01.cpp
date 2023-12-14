//
// Purpur Tentakel
// AOC 01/2023
//

#include "day_23_01.hpp"
#include "print.hpp"
#include "compare.hpp"
#include "load.hpp"
#include <string>
#include <algorithm>
#include <sstream>
#include <array>
#include <unordered_map>

static inline const std::string directory = R"(2023\input_23\day_23_01\)";

static inline const std::unordered_map<std::string, char> lookup{
	{ "one",   49 },
	{ "two",   50 },
	{ "three", 51 },
	{ "four",  52 },
	{ "five",  53 },
	{ "six",   54 },
	{ "seven", 55 },
	{ "eight", 56 },
	{ "nine",  57 },
};
static inline const std::array<std::string, 9> entries = {
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
};

[[nodiscard]] static char first_number(std::string const& s) {
	auto const number = std::find_if(s.cbegin(), s.cend(), [](char const c) { return std::isdigit(c); });
	if (number == s.cend()) {
		hlp::print(hlp::PrintType::ERROR, "no number in string found -> returning '0'");
		return 0;
	}
	return *number;
}
[[nodiscard]] static char last_number(std::string const& s) {
	auto const number = std::find_if(s.rbegin(), s.rend(), [](char const c) { return std::isdigit(c); });
	if (number == s.rend()) {
		hlp::print(hlp::PrintType::ERROR, "no number in string found -> returning '0'");
		return 0;
	}
	return *number;
}

[[nodiscard]] static int number(std::string const& s) {
	char const first = first_number(s);
	char const last = last_number(s);
	auto const number = std::string{ first } + last;
	return std::stoi(number);
}

[[nodiscard]] static int calculate(std::string const& input) {
	int i = 0;

	std::stringstream ss{ input };
	std::string line{ };

	while (std::getline(ss, line)) {
		i += number(line);
	}
	return i;
}

void day_23_01() {
	// test 1
	hlp::print(hlp::PrintType::TEST_1, "Day 1: Trebuchet?!");

	auto const input_1_test{ hlp::load(directory + "test1.txt") };
	auto const value_1_test{ calculate(input_1_test) };

    hlp::compare_and_print(142, value_1_test);

	// test 2
    hlp::print(hlp::PrintType::TEST_2, "Day 1: Trebuchet?!");

	hlp::print(hlp::PrintType::EXPECTED_RESULT, "281");
	auto const input_2_test{ hlp::load(directory + "test2.txt") };

    hlp::compare_and_print(281, 0);

	// task
	hlp::print(hlp::PrintType::TASK, "Day 1: Trebuchet?!");

	auto const input = hlp::load(directory + "input.txt");
	auto const value = calculate(input);
	// auto const value_with_number = calculate(input);
	hlp::print(hlp::PrintType::RESULT, "calibration value: {}", value);
	hlp::print(hlp::PrintType::FAIL, "to stupid for this");
}
