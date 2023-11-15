//
// Purpur Tentakel
// AOC 2015
//

#include "print.hpp"
#include <iostream>

std::string type_to_string(PrintType type) {
    switch (type) {
    case PrintType::NONE:
        return "";
    case PrintType::INFO:
        return "[INFO]";
    case PrintType::DEBUG:
        return "[DEBUG]";
    case PrintType::RESULT:
        return "[RESULT]";
    case PrintType::ERROR:
    default:
        return "[ERROR]";
    }
}

void print(PrintType type, std::string const& message) {
    if (type == PrintType::NONE) {
        std::cout << message << '\n';
        return;
    }
    std::cout << type_to_string(type) << ' ' << message << '\n';
}
