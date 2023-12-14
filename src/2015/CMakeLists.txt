add_library(2015
        STATIC
        days_15.hpp
        day_15_01/day_15_01.hpp
        day_15_01/day_15_01.cpp
        day_15_02/day_15_02.hpp
        day_15_02/day_15_02.cpp
        day_15_03/day_15_03.hpp
        day_15_03/day_15_03.cpp
)

target_link_libraries(2015 PRIVATE HELPER)