//
// Purpur Tentakel
// AOC 2015
//

#include "input.hpp"
#include "print.hpp"
#include <iostream>

int get_int_input(std::string const& message) {
	print(PrintType::NONE, message);

	auto valid_input{ false };
	int input;

	while (not valid_input) {
		std::string input_str{};
		std::cin >> input_str;


		try {
			input = std::stoi(input_str);
			valid_input = true;
		}
		catch (std::invalid_argument const&) {
			print(PrintType::NONE, "invalid input. try again");
		}
		catch (std::out_of_range const&) {
			print(PrintType::NONE, "value to big");
		}
	}

	return input;
}
