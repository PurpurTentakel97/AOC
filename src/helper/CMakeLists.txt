add_library(HELPER
        STATIC
        convert.hpp
        convert.cpp
        input.hpp
        input.cpp
        load.hpp
        load.cpp
        print.hpp
        print.cpp
        string.hpp
        string.cpp
        types.hpp
        compare.hpp
        compare.cpp
        concepts.hpp
)
target_include_directories(HELPER PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")