//
// Purpur Tentakel
// AOC
//

#pragma once

#include "2015/days_15.hpp"
#include "2023/days_23.hpp"

using function_map_ty = std::unordered_map<int, std::function<void()>>;

static inline function_map_ty map_day_15 {
	{  1, d_15_01::day_15_01 },
	{  2, d_15_02::day_15_02 },
	{  3, d_15_03::day_15_03 },
};

static inline function_map_ty map_day_23 {
	{  1, d_23_01::day_23_01 },
	{  2, d_23_02::day_23_02 },
	{  3, day_23_03 },
	{  4, day_23_04 },
	{  5, day_23_05 },
	{  6, day_23_06 },
};
