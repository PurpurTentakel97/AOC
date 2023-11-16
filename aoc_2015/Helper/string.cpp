//
// Purpur Tentakel
// AOC 2015
//

#include "string.hpp"
#include <sstream>

namespace hlp {
    std::vector<std::string> split(std::stringstream stream, char delimiter) {
        std::vector<std::string> entries{ };
        std::string entry{ };
        while (std::getline(stream, entry, delimiter)) {
            entries.push_back(entry);
        }
        return entries;
    }
}
