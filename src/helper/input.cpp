//
// Purpur Tentakel
// AOC helper
//

#include "input.hpp"
#include "print.hpp"
#include <iostream>

namespace hlp {
	int get_int_input(std::string const& message) {
		print(PrintType::INPUT, message);

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
				print(PrintType::ERROR, "invalid input. try again");
			}
			catch (std::out_of_range const&) {
				print(PrintType::ERROR, "value to big");
			}
		}

		return input;
	}
}
