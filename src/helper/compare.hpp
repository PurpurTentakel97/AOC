//
// Purpur Tentakel
// AOC helper
//

#pragma once

#include "concepts.hpp"
#include "print.hpp"

namespace hlp {
    template<IntegerType T>
    void compare_and_print(T expected, T provided) {
        auto const type = expected == provided ? hlp::PrintType::SUCCESS : hlp::PrintType::FAIL;
        hlp::print(type, "expected value: {}", expected);
        hlp::print(hlp::PrintType::NONE, "provided value: {}", provided);
    }
}
