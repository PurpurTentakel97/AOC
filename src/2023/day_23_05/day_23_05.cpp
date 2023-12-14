//
// Purpur Tentakel
// AOC 05/2023
//

#include "day_23_05.hpp"
#include "print.hpp"
#include "load.hpp"
#include "compare.hpp"

static const inline std::string title{"Day 5: If You Give A Seed A Fertilizer"};
static const inline std::string directory{R"(2023\input_23\day_23_05\)"};

void day_23_05() {
    using namespace hlp;
    print(PrintType::TEST_1, title);

    auto const input_test_1{load(directory + "test1.txt")};

    compare_and_print(35,0);
}
