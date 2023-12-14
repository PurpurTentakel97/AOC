add_subdirectory(helper)
add_subdirectory(2015)
add_subdirectory(2023)

add_executable(AOC
        main.cpp
        years.hpp
        years.cpp
        days.hpp
)

target_link_libraries(AOC PRIVATE HELPER)
target_link_libraries(AOC PRIVATE 2015)
target_link_libraries(AOC PRIVATE 2023)
