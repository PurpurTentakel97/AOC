//
// Purpur Tentakel
// AOC 2015
//

#include "load.hpp"
#include "print.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace hlp {
    std::string load(std::string const& f) {

        if (not std::filesystem::exists(f)) {
            print(PrintType::ERROR, "file does not exist: " + f);
            return { };
        }

        std::stringstream ss;
        std::ifstream file{ };
        file.open(f);

        if (not file.is_open()) {
            print(PrintType::ERROR, "not able to open file: " + f);
            return { };
        }

        std::string line;
        while (std::getline(file, line)) {
            ss << line << '\n';
        }

        file.close();
        return ss.str();
    }
}
