//
// Purpur Tentakel
// AOC 03/2015
//

#include "day_03.hpp"
#include "print.hpp"
#include "load.hpp"
#include <vector>
#include <set>

static constexpr inline char up   { '^' };
static constexpr inline char down { 'v' };
static constexpr inline char right{ '>' };
static constexpr inline char left { '<' };

struct Point final {
	int long long x, y;

	[[nodiscard]] bool operator==(Point const& other) const {
		return x == other.x 
			&& y == other.y;
	}

	[[nodiscard]] bool operator<(Point const& other) const {
		if (x == other.x) {
			return y < other.y;
		}
		return x < other.x;
	}
};

[[nodiscard]] static inline std::vector<Point> parse(std::string const& input) {
	std::vector<Point> points{ };
	Point current{ 0, 0 };

	for (auto const& c : input) {
		if (std::isspace(c)) {
			hlp::print(hlp::PrintType::INFO, "whitespace found -> ignoring");
			continue;
		}
		switch (c) {
			case up:
				++current.x;
				break;
			case down:
				--current.x;
				break;
			case right:
				++current.y;
				break;
			case left:
				--current.y;
				break;
			default:
				hlp::print(hlp::PrintType::ERROR, "unexpected token found : " + c);
				continue;
		}

		points.push_back(current);
	}

	return points;
}

[[nodiscard]] static inline std::set<Point> unique_points(std::vector<Point> points) {
	std::set<Point> u_points{ };

	for (auto p : points) {
		u_points.insert(p);
	}

	return u_points;
}

void day_03() {
	hlp::print_day(3);
	auto const input{ hlp::load("input\\input_03_1.txt") };

	auto const points{ parse(input) };
	auto const u_points{ unique_points(points) };

	hlp::print(hlp::PrintType::RESULT, "house count with min one present: " + std::to_string(u_points.size()));
}
