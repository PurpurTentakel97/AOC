//
// Purpur Tentakel
// AOC 02/2015
//

#include "day_02.hpp"
#include "types.hpp"
#include "print.hpp"
#include "load.hpp"
#include <vector>
#include <algorithm>
#include <sstream>

struct Package final {
	usize l, w, h;
};

[[nodiscard]] std::vector<Package> parse(std::string const& input) {
	std::vector<Package> packs{ };
	std::string line{ };
	std::stringstream stream{ input };
	while (std::getline(stream, line)) {

	}

	return packs;
}

[[nodiscard]] static inline usize surface_plus_extra(Package const& pck) {
	auto const l_w = pck.l * pck.w;
	auto const l_h = pck.l * pck.h;
	auto const w_h = pck.w * pck.h;
	return 2 * l_w + 2 * l_h + 2 * w_h + std::min(l_w, std::min(l_h, w_h));
}

void day_02() {
	hlp::print(hlp::PrintType::INFO, "day two called");
	auto const input{ hlp::load("input\\input_02_1.txt") };
	auto const packs{ parse(input) };

	usize surface{ 0 };
	for (auto const& pck : packs) {
		surface += surface_plus_extra(pck);
	}

	hlp::print(hlp::PrintType::RESULT, "the over all surface is " + std::to_string(surface) + " squarefeet");
}
