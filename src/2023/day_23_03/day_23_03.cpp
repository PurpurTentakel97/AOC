//
// Purpur Tentakel
// AOC 03/2023
//

#include "day_23_03.hpp"

#include "print.hpp"
#include "compare.hpp"
#include "load.hpp"

#include <sstream>

static inline const std::string directory = R"(2023\input_23\day_23_03\)";

static constexpr char gear  { '*' };
static constexpr char period{ '.' };

struct Symbol final {
	char symbol;
	int row, column;

	[[nodiscard]] bool is_symbol(char s) const {
		return s == symbol;
	}

	[[nodiscard]] bool is_row(int r) const {
		return r == row;
	}

	[[nodiscard]] bool is_column(int c) const {
		return c == column;
	}

	[[nodiscard]] bool is_point(int r, int c) const {
		return is_row(r) and is_column(c);
	}
};

struct Number final {
	int number;
	int row, left_column, right_column;

	[[nodiscard]] bool is_number(int n) const {
		return number == n;
	}

	[[nodiscard]] bool is_row(int r) const {
		return r == row;
	}

	[[nodiscard]] bool is_column(int c) const {
		return left_column <= c
			and right_column >= c;
	}

	[[nodiscard]] bool is_point(int r, int c) const {
		return is_row(r) and is_column(c);
	}

	[[nodiscard]] bool is_in_range(int r, int c) const {
		return  (row - 1) <= r
			and (row + 1) >= r
			and (left_column - 1) <= c
			and (right_column + 1) >= c;
	}

	[[nodiscard]] size_t length() const {
		return std::to_string(number).length();
	}
};

struct Field final {
	std::vector<Symbol> symbols{ };
	std::vector<Number> numbers{ };
	[[nodiscard]] std::vector<Number> numbers_next_to_symbols() const {
		std::vector<Number> result{ };
		for (auto const& number : numbers) {
			for (auto const& symbol : symbols) {
				if (number.is_in_range(symbol.row, symbol.column)) {
					result.push_back(number);
					break;
				}
			}
		}
		return result;
	}
};

[[nodiscard]] static int gear_count(Field field) {
	int count{ 0 };

	for (auto const& s : field.symbols) {
		if (s.symbol != gear) { continue; }
		std::vector<Number> numbers{ };
		for (auto const& n : field.numbers) {
			if (n.is_in_range(s.row, s.column)) {
				numbers.push_back(n);
			}
		}
		if (numbers.size() == 2) {
			count += (numbers[0].number * numbers[1].number);
		}
	}

	return count;
}

[[nodiscard]] static int sum_numbers(std::vector<Number> numbers) {
	int count{ };
	for (auto const& number : numbers) {
		count += number.number;
	}
	return count;
}

[[nodiscard]] static Number parse_number(std::string const& input, int index, int row, int column) {
	std::stringstream ss{ };
	int left_column{ column };
	for (int i = index; i < input.size(); ++i, ++column) {
		auto const c{ input[i] };
		if (not std::isdigit(c)) { --column;  break; }
		ss << c;
	}
	return { std::stoi(ss.str()), row, left_column, column };
}

[[nodiscard]] static Field parse(std::string const& input) {
	Field field{ };
	int row{ 0 };
	int column{ 0 };

	for (int i = 0; i < input.size(); ++i, ++column) {
		auto const c { input[i] };
		if (c == '\n') { ++row; column = -1; continue; }
		else if (std::isspace(c)) { continue; }
		else if (c == period) { continue; }
		else if (std::isdigit(c)) {
			auto const number{ parse_number(input, i, row, column) };
			field.numbers.push_back(number);
			i += static_cast<int>(number.length() - 1);
			column = number.right_column;
			continue;
		}
		else {
			field.symbols.emplace_back(c, row, column);
			continue;
		}
	}
	return field;
}

void day_23_03() {
	// test 1
	hlp::print(hlp::PrintType::TEST_1, "Day 3: Gear Ratios");

	auto const input_1_test{ hlp::load(directory + "test1.txt") };
	auto const field_1_test{ parse(input_1_test) };
	auto const numbers_1_test{ field_1_test.numbers_next_to_symbols() };
	auto const sum_1_test{ sum_numbers(numbers_1_test) };

    hlp::compare_and_print(4361, sum_1_test);

	// test 2
	hlp::print(hlp::PrintType::TEST_2, "Day 3: Gear Ratios");

	auto const input_2_test{ hlp::load(directory + "test2.txt") };
	auto const field_2_test{ parse(input_2_test) };
	auto const gears_2_test{ gear_count(field_2_test) };

    hlp::compare_and_print(467835, gears_2_test);

	// input
	hlp::print(hlp::PrintType::TASK, "Day 3: Gear Ratios");

    auto const input{ hlp::load(directory + "input.txt") };
	auto const field{ parse(input) };
	auto const numbers{ field.numbers_next_to_symbols() };
	auto const sum{ sum_numbers(numbers) };
	auto const gears{ gear_count(field) };

    hlp::print(hlp::PrintType::RESULT, "sum of all numbers next to a symbol: {}", sum);
    hlp::print(hlp::PrintType::RESULT, "sum of all gear ratios: {}", gears);
}
