//
// Purpur Tentakel
// AOC
//

#pragma once

#include "2015/days_15.hpp"
#include "2023/days_23.hpp"

using function_map_ty = std::unordered_map<int, std::function<void()>>;

static inline function_map_ty map_day_15 {
	{  1, day_15_01 },
	{  2, day_15_02 },
	{  3, day_15_03 },
};

static inline function_map_ty map_day_23 {
	{  1, day_23_01 },
	{  2, day_23_02 },
	{  3, day_23_03 },
	{  4, day_23_04 },
	{  5, day_23_05 },
};
