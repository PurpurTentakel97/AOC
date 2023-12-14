//
// Purpur Tentakel
// AOC
//

#include "years.hpp"
#include "helper/print.hpp"
#include "helper/input.hpp"

void years(int const year, std::unordered_map<int, std::function<void()>> map) {

	hlp::print_call_year(year);

	auto running{ true };

	while (running) {
		hlp::print_map(map);
		auto const input{ hlp::get_int_input("choose a day | 0 exists the year.") };
		if (map.contains(input)) {
			hlp::print_call_day(input);
			map[input]();
			hlp::print(hlp::PrintType::QUIT, "quit day");
		}
		else if (input == 0) {
			hlp::print(hlp::PrintType::QUIT, "0. returning to menu");
			running = false;
		}
		else {
			hlp::print(hlp::PrintType::ERROR, "day not existing");
		}
	}
}
