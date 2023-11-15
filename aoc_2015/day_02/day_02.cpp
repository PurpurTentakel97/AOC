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

static struct Package final {
	usize l, w, h;
};

[[nodiscard]] static inline std::vector<Package> parse(std::string const&) {

}

[[nodiscard]] static inline usize surface_plus_extra(Package const& pck) {
	auto const l_w = pck.l * pck.w;
	auto const l_h = pck.l * pck.h;
	auto const w_h = pck.w * pck.h;
	return 2 * l_w + 2 * l_h + 2 * w_h + std::min(l_w, l_h, w_h);
}

void day_02() {
	print(PrintType::INFO, "day two called");
	auto const input{ load("input\\input_02_1.txt") };
	auto const pcks{ parse(input) };

	usize surface{ 0 };
	for (auto const& pck : pcks) {
		surface += surface_plus_extra(pck);
	}

	print(PrintType::RESULT, "the over all surface is " + std::to_string(surface) + "squarefeet");
}
