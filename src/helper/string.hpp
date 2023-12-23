//
// Purpur Tentakel
// AOC helper
//

#pragma once

#include <vector>
#include <string>
#include <format>
#include "print.hpp"

namespace hlp {
	[[nodiscard]] std::vector<std::string> split(std::stringstream entry, char delimiter);

    [[nodiscard]] std::string flip(std::string s);

    [[nodiscard]] bool is_multiple_digit(std::string const& s);

    template<typename... Args>
    std::string str(std::string const& text, Args const& ...args) {
        try{
            std::string const out{std::vformat(text, std::make_format_args(args...))};
            return out;
        } catch (std::format_error const&) {
            print(PrintType::ERROR, "format while printing with arguments");
            print(PrintType::NONE, text);
        } catch (std::bad_alloc const&){
            print(PrintType::ERROR, "bad alloc while printing with arguments");
            print(PrintType::NONE, text);
        }
        return text;
    }

	void ltrim(std::string& s);
	void rtrim(std::string& s);
	void trim (std::string& s);

	[[nodiscard]] std::string ltrim_copy(std::string s);
	[[nodiscard]] std::string rtrim_copy(std::string s);
	[[nodiscard]] std::string trim_copy (std::string s);
}
