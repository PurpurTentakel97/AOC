//
// Purpur Tentakel
// AOC helper
//

#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <format>

namespace hlp {
	enum class PrintType {
		DEBUG,
		INFO,
		ERROR,
		RESULT,
		EXPECTED_RESULT,
		CALL,
		INPUT,
		TASK,
		TEST_1,
		TEST_2,
        SUCCESS,
        FAIL,
		QUIT,
		NONE,
	};

	[[nodiscard]] static constexpr std::string type_to_string(PrintType type) {
        switch (type) {
            case PrintType::NONE:
                return "";
            case PrintType::INFO:
                return "[INFO]";
            case PrintType::DEBUG:
                return "[DEBUG]";
            case PrintType::RESULT:
                return "[RESULT]";
            case PrintType::EXPECTED_RESULT:
                return "[EXPECTED_RESULT]";
            case PrintType::CALL:
                return "[CALL]";
            case PrintType::INPUT:
                return "[INPUT]";
            case PrintType::TASK:
                return "[TASK]";
            case PrintType::TEST_1:
                return "[TEST_1]";
            case PrintType::TEST_2:
                return "[TEST_2]";
            case PrintType::SUCCESS:
                return "[SUCCESS]";
            case PrintType::FAIL:
                return "[FAIL]";
            case PrintType::QUIT:
                return "[QUIT]";
            case PrintType::ERROR:
                return "[ERROR]";
        }
        return "[ERROR]";
    }

    void print(PrintType type, std::string const& message);

    template<typename... Args>
    void print(PrintType type, std::string const& message, Args const& ...args) {
        std::string const typeS {type_to_string(type)};

        try{
            std::string const out{std::vformat(message, std::make_format_args(args...))};
            print(type, out);
        } catch (std::format_error const&) {
            print(PrintType::ERROR, "format while printing with arguments");
            print(type, message);
        } catch (std::bad_alloc const&){
            print(PrintType::ERROR, "bad alloc while printing with arguments");
            print(type, message);
        }
    }

	void print_call_day(int n);

	void print_quit_day(int n);

	void print_call_year(int n);

	void print_whitespace_ignore();

	void print_unexcepted_character(char c);

	template<typename T = std::function<void()>>
	void print_map(std::unordered_map<int, T> map, int exit_number = 0) {
		print(PrintType::INFO, "available numbers:");
		print(PrintType::INFO, "-> " + std::to_string(exit_number));

		for (auto const& [number, unused] : map) {
			print(PrintType::INFO, "-> " + std::to_string(number));
		}
	}
}
