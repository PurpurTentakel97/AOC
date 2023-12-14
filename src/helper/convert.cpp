//
// Purpur Tentakel
// AOC helper
//

#include "convert.hpp"
#include "print.hpp"
#include <iostream>

namespace hlp {
	int st_to_i(std::string const& s) {
        try {
            return std::stoi(s);
        }
		catch (std::invalid_argument const&) {
			print(PrintType::NONE, "invalid input. try again. -> " + s);
			return 0;
		}
		catch (std::out_of_range const&) {
			print(PrintType::NONE, "value to big -> " + s);
			return 0;
		}
    }
}
