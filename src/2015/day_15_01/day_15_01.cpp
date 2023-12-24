//
// Purpur Tentakel
// AOC 01/2015
//

#include "day_15_01.hpp"
#include "print.hpp"
#include "load.hpp"
#include "compare.hpp"
#include "string.hpp"
#include <unordered_map>
#include <cctype>
#include <string>

namespace d_15_01 {
    static inline const std::string directory = R"(src\2015\input_15\day_15_01\)";

    static constexpr char add{ '(' };
    static constexpr char sub{ ')' };
    static inline std::unordered_map<char, int> operation{
            { add, 1 },
            { sub, -1 },
    };

    [[nodiscard]] static std::pair<int, int> calculate(std::string const &input) {
        auto count{ 0 };
        auto pos{ 0 };
        auto found{ false };

        for (auto const &c : input) {
            if (std::isspace(c)) {
                continue;
            }
            if (not operation.contains(c)) {
                hlp::print(hlp::PrintType::ERROR, "unexpected character: {}", c);
                continue;
            }

            count += operation[c];
            if (not found) {
                ++pos;
            }
            if (count < 0) {
                found = true;
            }
        }
        return { count, pos };
    }

    void day_15_01() {
        // test 1
        hlp::print(hlp::PrintType::TEST_1, "Not Quite Lisp");

        auto const test1_input{ hlp::load(directory + "test1.txt") };
        auto const [test1_count, unused_1] = calculate(test1_input);

        hlp::compare_and_print(3, test1_count);

        // test 2
        hlp::print(hlp::PrintType::TEST_2, "Not Quite Lisp");

        auto const test2_input{ hlp::load(directory + "test2.txt") };
        auto const [unused_2, test2_pos] = calculate(test2_input);

        hlp::compare_and_print(5, test2_pos);

        // task
        hlp::print(hlp::PrintType::TASK, "Not Quite Lisp");

        auto const input{ hlp::load(directory + "input.txt") };
        auto const [count, pos] = calculate(input);

        hlp::print(hlp::PrintType::RESULT, "final count: " + std::to_string(count));
        hlp::print(hlp::PrintType::RESULT, "first position smaller than 0: " + std::to_string(pos));
    }
}
