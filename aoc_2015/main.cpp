//
// Purpur Tentakel
// AOC 2015
//

#include "input.hpp"
#include "print.hpp"
#include "days.hpp"
#include <unordered_map>
#include <functional>

static inline std::unordered_map<int, std::function<void()>> map{
	{ 1 , day_01 },
	{ 2 , day_02 },
};

int main() { 
	auto running{ true };

	while(running) {
		auto const input{ hlp::get_int_input("choose a day | 0 exists the app.") };
		if (map.contains(input)) {
			map[input]();
		}
		else if (input == 0) {
			hlp::print(hlp::PrintType::NONE, "0. exit app");
			running = false;
		}
		else {
			hlp::print(hlp::PrintType::NONE, "input out of range");
		}
	}
}
