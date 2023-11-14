//
// Purpur Tentakel
// AOC 2015
//

#include "Helper/input.hpp"
#include "Helper/print.hpp"
#include <unordered_map>
#include <functional>

int main() { 
	auto running{ true };

	std::unordered_map<int, std::function<void()>> map{ };

	while(running) {
		auto input{ get_int_input("choose a day | invalid number exists the app.") };
		if (map.contains(input)) {
			map[input]();
		}
		else {
			print(PrintType::NONE, "other input. exit app");
			running = false;
		}
	}
}