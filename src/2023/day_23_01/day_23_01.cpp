//
// Purpur Tentakel
// AOC 01/2023
//

#include "day_23_01.hpp"
#include "print.hpp"
#include "compare.hpp"
#include "load.hpp"
#include "string.hpp"
#include <string>
#include <algorithm>
#include <sstream>
#include <array>
#include <unordered_map>

namespace d_23_01 {
    static inline const std::string directory = R"(src\2023\input_23\day_23_01\)";

    static inline const std::unordered_map<std::string, char> l_lookup{
            { "one",   '1' },
            { "two",   '2' },
            { "three", '3' },
            { "four",  '4' },
            { "five",  '5' },
            { "six",   '6' },
            { "seven", '7' },
            { "eight", '8' },
            { "nine",  '9' },
    };
    static inline const std::unordered_map<std::string, char> r_lookup{
            { "eno",   '1' },
            { "owt",   '2' },
            { "eerht", '3' },
            { "ruof",  '4' },
            { "evif",  '5' },
            { "xis",   '6' },
            { "neves", '7' },
            { "thgie", '8' },
            { "enin",  '9' },
    };

    [[nodiscard]] static int number(std::string const &s) {
        auto const find_number{ [](std::string const &s) -> char {
            auto const number = std::find_if(s.cbegin(), s.cend(), [](char const c) { return std::isdigit(c); });
            if (number == s.cend()) {
                hlp::print(hlp::PrintType::ERROR, "no number in string found -> returning '0'");
                return 0;
            }
            return *number;
        }};
        char const first = find_number(s);
        char const last = find_number(hlp::flip(s));
        auto const number = std::string{ first } + last;
        return std::stoi(number);
    }

    [[nodiscard]] static int number_with_char(std::string const &s) {
        auto const find_number{ [](std::string const &s, std::unordered_map<std::string, char> const &lookup) -> char {
            for (int i = 0; i < s.size(); ++i) {
                if (std::isdigit(static_cast<unsigned char>(s[i]))) {
                    return s[i];
                }
                for (auto const &[key, value] : lookup) {
                    if (s.rfind(key, i) != std::string::npos) {
                        return value;
                    }
                }
            }
            return 0;
        }};

        auto const first{ find_number(s, l_lookup) };
        auto const second{ find_number(hlp::flip(s), r_lookup) };
        auto const number{ std::string{ first } + second };
        return std::stoi(number);
    }

    [[nodiscard]] static int calculate(std::string const &input, bool with_char) {
        int i = 0;

        std::stringstream ss{ input };
        std::string line{ };

        while (std::getline(ss, line)) {
            if (with_char) {
                i += number_with_char(line);
            } else {
                i += number(line);
            }
        }
        return i;
    }

    void day_23_01() {
        // test 1
        hlp::print(hlp::PrintType::TEST_1, "Day 1: Trebuchet?!");

        auto const input_1_test{ hlp::load(directory + "test1.txt") };
        auto const value_1_test{ calculate(input_1_test, false) };

        hlp::compare_and_print(142, value_1_test);

        // test 2
        hlp::print(hlp::PrintType::TEST_2, "Day 1: Trebuchet?!");

        auto const input_2_test{ hlp::load(directory + "test2.txt") };
        auto const value_2_test{ calculate(input_2_test, true) };

        hlp::compare_and_print(281, value_2_test);

        // task
        hlp::print(hlp::PrintType::TASK, "Day 1: Trebuchet?!");

        auto const input = hlp::load(directory + "input.txt");
        auto const value = calculate(input, false);
        auto const value_with_number = calculate(input, true);
        hlp::print(hlp::PrintType::RESULT, "calibration value: {}", value);
        hlp::print(hlp::PrintType::RESULT, "value with chars: {}", value_with_number);
    }
}
