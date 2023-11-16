//
// Purpur Tentakel
// AOC 2015
//

#include "print.hpp"
#include <iostream>

namespace hlp {
    std::string type_to_string(PrintType const type) {
        switch (type) {
            case PrintType::NONE:
                return "";
            case PrintType::INFO:
                return "[INFO]";
            case PrintType::DEBUG:
                return "[DEBUG]";
            case PrintType::RESULT:
                return "[RESULT]";
            case PrintType::CALL:
                return "[CALL]";
            case PrintType::INPUT:
                return "[INPUT]";
            case PrintType::QUIT:
                return "[QUIT]";
            case PrintType::ERROR:
                return "[ERROR]";
        }
        return "[ERROR]";
    }

    void print(PrintType const type, std::string const& message) {
        if (type == PrintType::NONE) {
            std::cout << message << '\n';
            return;
        }
        std::cout << type_to_string(type) << ' ' << message << '\n';
    }

    void print_day(int n) {
        print(PrintType::CALL, "day " + std::to_string(n));
    }

    void print_whitespace_ignore() { 
        print(PrintType::INFO, "whitespace found -> ignored");
    }

    void print_unexcepted_character(char c) {
        print(PrintType::ERROR, "unexpected character: " + c);
    }
}
