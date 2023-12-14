//
// Purpur Tentakel
// AOC helper
//

#pragma once

#include <concepts>

namespace hlp {
    template<typename n> concept IntegerType = requires(n number) {
        requires std::is_integral_v<n>;
        requires !std::is_same_v<bool, n>;
        requires !std::is_pointer_v<n>;
    };
}
