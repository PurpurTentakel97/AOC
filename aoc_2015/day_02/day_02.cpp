//
// Purpur Tentakel
// AOC 02/2015
//

#include "day_02.hpp"
#include "types.hpp"
#include "print.hpp"
#include "load.hpp"
#include "string.hpp"
#include "convert.hpp"
#include <vector>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <array>

struct Package final {
	usize l, w, h;
};

[[nodiscard]] std::vector<Package> parse(std::string const& input) {
	std::vector<Package> packs{ };
	std::string line{ };
	std::stringstream stream{ input };
	while (std::getline(stream, line)) {
		auto entries = hlp::split(std::stringstream{ line }, 'x');
		assert(entries.size() == 3);
		packs.emplace_back(
			hlp::st_to_i(entries[0]),
			hlp::st_to_i(entries[1]),
			hlp::st_to_i(entries[2])
		);
	}

	return packs;
}

[[nodiscard]] static inline usize surface_plus_extra(std::vector<Package> const& packs) {
	usize surface{ };

	for (auto const& pck : packs) {
		auto const l_w = pck.l * pck.w;
		auto const l_h = pck.l * pck.h;
		auto const w_h = pck.w * pck.h;
		auto single{ 2 * l_w + 2 * l_h + 2 * w_h + std::min(l_w, std::min(l_h, w_h)) };
		surface += single;
	}

	return surface;
}

[[nodiscard]] static inline usize ribbon_and_tie(std::vector<Package> const& packs) {
	usize ribbon{ };

	for (auto const& pck : packs) {
		auto const tie{ pck.h * pck.l * pck.w };
		auto numbers{ std::array<usize,3>{pck.h,pck.l,pck.w} };
		std::sort(numbers.begin(), numbers.end());
		auto const rib{ 2 * numbers[0] + 2 * numbers[1] };
		ribbon += tie + rib;
	}

	return ribbon;
}

void day_02() {
	hlp::print(hlp::PrintType::INFO, "day two called");
	auto const input{ hlp::load("input\\input_02_1.txt") };
	auto const packs{ parse(input) };

	auto const surface{ surface_plus_extra(packs) };
	auto const ribbon{ ribbon_and_tie(packs) };

	hlp::print(hlp::PrintType::RESULT, "the over all surface is " + std::to_string(surface) + " squarefeet");
	hlp::print(hlp::PrintType::RESULT, "the over all ribbon is " + std::to_string(ribbon) + " feet");
}
