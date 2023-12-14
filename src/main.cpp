//
// Purpur Tentakel
// AOC
//

#include "years.hpp"
#include "days.hpp"
#include "helper/input.hpp"
#include "helper/print.hpp"

#include <unordered_map>

static inline std::unordered_map<int, function_map_ty> map_years{
	{  15, map_day_15 },
	{  23, map_day_23 },
};

int main() { 
	auto running{ true };

	while(running) {
		hlp::print_map(map_years);
		auto const input{ hlp::get_int_input("choose a year | 0 exists the app.") };
		if (map_years.contains(input)) {
			years(input, map_years[input]);
		}
		else if (input == 0) {
			hlp::print(hlp::PrintType::QUIT, "0. exit app");
			running = false;
		}
		else {
			hlp::print(hlp::PrintType::ERROR, "day not existing");
		}
	}
}
