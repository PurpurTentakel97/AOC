//
// Purpur Tentakel
// AOC 2015
//

#include "load.hpp"
#include "print.hpp"
#include <fstream>
#include <sstream>

std::string load(std::string const& f) {
    std::stringstream ss;
    std::ifstream file{ f };

    if (not file.is_open()) {
        print(PrintType::ERROR, "not able to open file: " + f);
        return { };
    }

    while (file.peek() != EOF) {
        ss << static_cast<char>(file.get());
    }
    file.close();
    return ss.str();
}
