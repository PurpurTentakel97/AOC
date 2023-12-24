add_library(2023
            STATIC
            days_23.hpp
            day_23_01/day_23_01.hpp
            day_23_01/day_23_01.cpp
            day_23_02/day_23_02.hpp
            day_23_02/day_23_02.cpp
            day_23_03/day_23_03.hpp
            day_23_03/day_23_03.cpp
            day_23_04/day_23_04.hpp
            day_23_04/day_23_04.cpp
            day_23_05/day_23_05.hpp
            day_23_05/day_23_05.cpp
            day_23_06/day_23_06.hpp
            day_23_06/day_23_06.cpp
            day_23_07/day_23_07.hpp
            day_23_07/day_23_07.cpp
)

target_link_libraries(2023 PRIVATE HELPER)
