//
// Purpur Tentakel
// AOC helper
//

#include "print.hpp"
#include "types.hpp"
#include <iostream>
#include <iomanip>

namespace hlp {

    [[nodiscard]] static constexpr usize label_length(PrintType type) {
        return type_to_string(type).length();
    }

    static constexpr usize longest_type_count{ label_length(PrintType::EXPECTED_RESULT)};

    void print(PrintType const type, std::string const& message) {
        std::cout << std::setw(longest_type_count) << std::right << type_to_string(type) << ' ' << message << '\n';
    }

    void print_call_day(int n) {
        print(PrintType::CALL, "day " + std::to_string(n));
    }

    void print_quit_day(int n) {
        print(PrintType::QUIT, "day " + std::to_string(n));
    }

    void print_call_year(int n) {
        print(PrintType::CALL, "year " + std::to_string(n));
    }

    void print_whitespace_ignore() { 
        print(PrintType::INFO, "whitespace found -> ignored");
    }

    void print_unexcepted_character(char c) {
        print(PrintType::ERROR, "unexpected character: " + c);
    }
}
