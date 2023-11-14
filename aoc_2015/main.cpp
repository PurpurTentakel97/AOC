//
// Purpur Tentakel
// AOC 2015
//

#include "input.hpp"
#include "print.hpp"
#include "days.hpp"
#include <unordered_map>
#include <functional>

int main() { 
	auto running{ true };

	std::unordered_map<int, std::function<void()>> map{
		{ 1 , day_01 },
	};

	while(running) {
		auto input{ get_int_input("choose a day | 0 exists the app.") };
		if (map.contains(input)) {
			map[input]();
		}
		else if (input == 0) {
			print(PrintType::NONE, "0. exit app");
			running = false;
		}
		else {
			print(PrintType::NONE, "input out of range");
		}
	}
}
