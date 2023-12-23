//
// Purpur Tentakel
// AOC 06/2023
//

#include "day_23_06.hpp"
#include "print.hpp"
#include "load.hpp"
#include "types.hpp"
#include "string.hpp"
#include <string>
#include <sstream>
#include <cassert>
#include "compare.hpp"

static inline const std::string title{ "Day 6: Wait For It" };
static inline const std::string directory{ R"(src\2023\input_23\day_23_06\)" };

struct Race final {
    usize time, distance, win_count;

    void print() const {
        hlp::print(hlp::PrintType::DEBUG, "Race:");
        hlp::print(hlp::PrintType::NONE, "time: {}", time);
        hlp::print(hlp::PrintType::NONE, "distance: {}", distance);
        hlp::print(hlp::PrintType::NONE, "win count: {}", win_count);
    }
};

using Races = std::vector<Race>;

static inline Races parse(std::string const &input) {
    auto lines{ hlp::split(std::stringstream{ input }, '\n') };
    assert(lines.size() == 2);

    auto const times_raw{ hlp::split(std::stringstream{ lines[0] }, ' ') };
    auto const distances_raw{ hlp::split(std::stringstream{ lines[1] }, ' ') };

    auto const remove_non_digits([](std::vector<std::string> const &input) -> std::vector<usize> {
        std::vector<usize> output{ };
        for (auto const &ch : input) {
            if (hlp::is_multiple_digit(ch)) {
                output.push_back(static_cast<usize>(std::stoi(ch)));
            }
        }
        return output;
    });

    auto const times{ remove_non_digits(times_raw) };
    auto const distances{ remove_non_digits(distances_raw) };

    assert(times.size() == distances.size());

    Races races{ };
    for (usize i = 0; i < times.size(); ++i) {
        Race race{
                times[i],
                distances[i],
                0
        };
        races.push_back(race);
    }
    return races;
}

static inline usize calculate_distance(usize time, usize speed) {
    return time * speed;
}

static inline usize simulate_distance(Races &races) {
    for (auto &race : races) {
        for (usize i = 0; i <= race.time; ++i) {
            auto const distance{ calculate_distance(race.time - i, i) };
            if (distance > race.distance) {
                ++race.win_count;
            }
        }
    }
    usize result{ 1 };
    for (auto const &race : races) {
        result *= race.win_count;
    }
    return result;
}


void day_23_06() {
    using namespace hlp;
    // test 1
    print(PrintType::TEST_1, title);

    auto const input_test_1{ load(directory + "test1.txt") };
    auto races_test_1{ parse(input_test_1) };
    auto const win_count_test_1{ simulate_distance(races_test_1) };

    compare_and_print(usize{ 288 }, win_count_test_1);

    // test 2
    print(PrintType::TEST_2, title);
    print(PrintType::ERROR, "not able to solve");

    // task
    print(PrintType::TASK, title);

    auto const input{ load(directory + "input.txt") };
    auto races{ parse(input) };
    auto const win_count{ simulate_distance(races) };

    print(PrintType::RESULT, "the multiply of all win counts is {}", win_count);
}
