//
// Purpur Tentakel
// AOC 02/2015
//

#include "day_15_02.hpp"
#include "print.hpp"
#include "load.hpp"
#include "string.hpp"
#include "convert.hpp"
#include "compare.hpp"
#include <vector>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <array>

static inline const std::string directory = R"(2015\input_15\day_15_02\)";

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

void day_15_02() {
	// test 1
	hlp::print(hlp::PrintType::TEST_1, "I Was Told There Would Be No Math");

	auto const input_1_test{ hlp::load(directory + "test1.txt") };
	auto const packs_1_test{ parse(input_1_test) };
	auto const surface_1_test{ surface_plus_extra(packs_1_test) };
	
    hlp::compare_and_print(usize{ 101 }, surface_1_test);

	// test 2
	hlp::print(hlp::PrintType::TEST_2, "I Was Told There Would Be No Math");

	auto const input_2_test{ hlp::load(directory + "test2.txt") };
	auto const packs_2_test{ parse(input_2_test) };
	auto const ribbon_2_test{ ribbon_and_tie(packs_2_test) };
	
    hlp::compare_and_print(usize{ 48 }, ribbon_2_test);

	// task
	hlp::print(hlp::PrintType::TASK, "I Was Told There Would Be No Math");
	
	auto const input{ hlp::load(directory + "input.txt") };
	auto const packs{ parse(input) };
	auto const surface{ surface_plus_extra(packs) };
	auto const ribbon{ ribbon_and_tie(packs) };
	
	hlp::print(hlp::PrintType::RESULT, "the over all surface is {} squarefeet", surface);
	hlp::print(hlp::PrintType::RESULT, "the over all ribbon is {} feet", ribbon);
}
