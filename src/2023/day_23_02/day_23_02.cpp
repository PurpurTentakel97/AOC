//
// Purpur Tentakel
// AOC 02/2023
//

#include "day_23_02.hpp"
#include "print.hpp"
#include "compare.hpp"
#include "load.hpp"
#include "string.hpp"

#include <cassert>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>

namespace d_23_02 {
    static inline const std::string directory = R"(src\2023\input_23\day_23_02\)";

    struct Round final {
        int r{ 0 };
        int g{ 0 };
        int b{ 0 };

        void add_red(int n) {
            r += n;
        }

        void add_green(int n) {
            g += n;
        }

        void add_blue(int n) {
            b += n;
        }

        std::unordered_map<std::string, std::function<void(int)>> look_up{
                { "red",   [this](int n) { add_red(n); }},
                { "green", [this](int n) { add_green(n); }},
                { "blue",  [this](int n) { add_blue(n); }},
        };

        [[nodiscard]] bool is_possible(int r_, int g_, int b_) const {
            return r <= r_
                   and g <= g_
                   and b <= b_;
        }

        [[nodiscard]] int multiply() const {
            return r * g * b;
        }

        void print() const {
            hlp::print(hlp::PrintType::DEBUG,
                       "Round: | r: {} | g: {} | b: {}", r, g, b
            );
        }
    };

    struct Game final {
        int id = 0;
        std::vector<Round> rounds{ };

        [[nodiscard]] bool is_possible(int r, int g, int b) const {
            for (auto const &round : rounds) {
                if (not round.is_possible(r, g, b)) {
                    return false;
                }
            }
            return true;
        }

        [[nodiscard]] Round lowest_possible_amount_cubes() const {
            Round result{ };
            for (auto const &round : rounds) {
                if (result.r < round.r) {
                    result.r = round.r;
                }
                if (result.g < round.g) {
                    result.g = round.g;
                }
                if (result.b < round.b) {
                    result.b = round.b;
                }
            }
            return result;
        }

        void print() const {
            hlp::print(hlp::PrintType::DEBUG, "Game: | id: {}", id);
            for (auto const &round : rounds) {
                round.print();
            }
        }
    };

    using games_ty = std::vector<Game>;

    [[nodiscard]] static int parse_game_name(std::string &input) {
        hlp::trim(input);
        auto const result{ hlp::split(std::stringstream{ input }, ' ') };
        assert(result.size() == 2);
        return std::stoi(result[1]);
    }

    [[nodiscard]] static std::vector<Round> parse_game_entries(std::string &input) {
        hlp::trim(input);
        std::vector<Round> rounds{ };

        auto sets{ hlp::split(std::stringstream{ input }, ';') };
        for (auto &single_set : sets) {
            Round round{ };
            hlp::trim(single_set);
            auto cubes{ hlp::split(std::stringstream{ single_set }, ',') };
            for (auto &cube : cubes) {
                hlp::trim(cube);
                auto const cube_parts{ hlp::split(std::stringstream{ cube }, ' ') };
                assert(cube_parts.size() == 2);
                round.look_up[cube_parts[1]](std::stoi(cube_parts[0]));
            }
            rounds.push_back(round);
        }

        return rounds;
    }

    [[nodiscard]] static games_ty parse(std::string const &input) {
        games_ty games{ };
        std::stringstream ss{ input };
        std::string line{ };

        while (std::getline(ss, line)) {
            auto result = hlp::split(std::stringstream{ line }, ':');
            assert(result.size() == 2);
            Game game{ };
            game.id = parse_game_name(result[0]);
            game.rounds = parse_game_entries(result[1]);
            games.push_back(game);
        }

        return games;
    }

    [[nodiscard]] static std::pair<games_ty, games_ty>
    possible_impossible_games(games_ty const &games, int r, int g, int b) {
        std::pair<games_ty, games_ty> result{ };
        for (auto const &game : games) {
            if (game.is_possible(r, g, b)) {
                result.first.push_back(game);
            } else {
                result.second.push_back(game);
            }
        }
        return result;
    }

    [[nodiscard]] static int sum_game_ids(games_ty games) {
        int count{ };
        for (auto const &game : games) {
            count += game.id;
        }
        return count;
    }


    [[nodiscard]] static std::vector<Round> lowest_possible_cube_counts(games_ty games) {
        std::vector<Round> result{ };
        for (auto const &game : games) {
            result.push_back(game.lowest_possible_amount_cubes());
        }
        return result;
    }

    [[nodiscard]] static int sum_lowest_cubes(std::vector<Round> rounds) {
        int count{ };
        for (auto const &round : rounds) {
            count += round.multiply();
        }
        return count;
    }

    void day_23_02() {
        // test 1
        hlp::print(hlp::PrintType::TEST_1, "Day 2: Cube Conundrum");

        auto const input_1_test{ hlp::load(directory + "test1.txt") };
        auto const games_1_test{ parse(input_1_test) };
        auto const calculated_games_1_test{ possible_impossible_games(games_1_test, 12, 13, 14) };
        auto const id_count_1_test{ sum_game_ids(calculated_games_1_test.first) };

        hlp::compare_and_print(8, id_count_1_test);

        // test 2
        hlp::print(hlp::PrintType::TEST_2, "Day 2: Cube Conundrum");

        auto const input_2_test{ hlp::load(directory + "test2.txt") };
        auto const games_2_test{ parse(input_2_test) };
        auto const lowest_cubes_2_test{ lowest_possible_cube_counts(games_2_test) };
        auto const cube_count_2_test{ sum_lowest_cubes(lowest_cubes_2_test) };

        hlp::compare_and_print(2286, cube_count_2_test);

        // input
        hlp::print(hlp::PrintType::TASK, "Day 2: Cube Conundrum");

        auto const input{ hlp::load(directory + "input.txt") };
        auto const games{ parse(input) };
        auto const calculated_games{ possible_impossible_games(games, 12, 13, 14) };
        auto const id_count{ sum_game_ids(calculated_games.first) };
        auto const lowest_cubes{ lowest_possible_cube_counts(games) };
        auto const cube_count{ sum_lowest_cubes(lowest_cubes) };

        hlp::print(hlp::PrintType::RESULT, "sum of possible game ids: {}", id_count);
        hlp::print(hlp::PrintType::RESULT, "lowest possible cube count: {}", cube_count);
    }
}
