//
// Purpur Tentakel
// AOC helper
//

#include "string.hpp"
#include <sstream>
#include <algorithm>

namespace hlp {
    std::vector<std::string> split(std::stringstream stream, char delimiter) {
        std::vector<std::string> entries{ };
        std::string entry{ };
        while (std::getline(stream, entry, delimiter)) {
            entries.push_back(entry);
        }
        return entries;
    }

    std::string flip(std::string s) {
        std::reverse(s.begin(), s.end());
        return s;
    }

    bool is_multiple_digit(const std::string &s) {
        if (s.empty()) {
            return false;
        }
        return std::all_of(s.begin(), s.end(), [](char const &c) -> bool {
            return std::isdigit(static_cast<unsigned char>(c));
        });
    }

    void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](auto const &ch) { return !std::isspace(ch); }));
    }

    void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](auto const &ch) { return !std::isspace(ch); }).base(), s.end());
    }

    void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    std::string ltrim_copy(std::string s) {
        ltrim(s);
        return s;
    }

    std::string rtrim_copy(std::string s) {
        rtrim(s);
        return s;
    }

    std::string trim_copy(std::string s) {
        trim(s);
        return s;
    }
}
