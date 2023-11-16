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

[[nodiscard]] static inline std::vector<Point> parse_one(std::string const& input) {
	Point current{ 0, 0 };
	std::vector<Point> points{ current };

	for (auto const& c : input) {
		if (std::isspace(c)) {
			hlp::print_whitespace_ignore();
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
				hlp::print_unexcepted_character(c);
				continue;
		}

		points.push_back(current);
	}

	return points;
}

[[nodiscard]] static inline std::vector<Point> parse_two(std::string const& input) {
	Point santa{ 0,0 };
	Point santa_robot{ 0,0 };
	std::vector<Point> points{ santa };
	auto count{ 0 };

	for (auto const& c : input) {
		if (std::isspace(c)) {
			hlp::print_whitespace_ignore();
			continue;
		}

		Point* const dummy{ count % 2 == 0 ? &santa : &santa_robot };

		switch (c) {
			case up:
				++dummy->x;
				break;
			case down:
				--dummy->x;
				break;
			case right:
				++dummy->y;
				break;
			case left:
				--dummy->y;
				break;
			default:
				hlp::print_unexcepted_character(c);
				continue;
		}

		++count;
		points.push_back(*dummy);
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

	auto const santa_points{ parse_one(input) };
	auto const u_santa_points{ unique_points(santa_points) };

	auto const robot_points{ parse_two(input) };
	auto const u_robot_points{ unique_points(robot_points) };

	hlp::print(hlp::PrintType::RESULT, "house count with min one present: " + std::to_string(u_santa_points.size()));
	hlp::print(hlp::PrintType::RESULT, "house count with min one present with robot Santa: " + std::to_string(u_robot_points.size()));
}
