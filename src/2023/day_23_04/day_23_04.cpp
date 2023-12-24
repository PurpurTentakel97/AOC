//
// Purpur Tentakel
// AOC 04/2023
//

#include "day_23_04.hpp"
#include "load.hpp"
#include "print.hpp"
#include "types.hpp"
#include "string.hpp"
#include "compare.hpp"
#include <vector>
#include <set>
#include <sstream>
#include <unordered_map>

namespace d_23_04 {
    static inline const std::string directory = R"(src\2023\input_23\day_23_04\)";

    class Card final {
    private:
        using number_vec_ty = std::set<usize>;
        usize m_number;
        number_vec_ty m_winning{ };
        number_vec_ty m_provided{ };
        usize m_points{ 0 };

    public:
        Card(usize number, number_vec_ty winning, number_vec_ty provided)
                : m_number{ number }, m_winning{ std::move(winning) }, m_provided{ std::move(provided) } {
        }

        [[nodiscard]] number_vec_ty winning() const {
            return m_winning;
        }

        [[nodiscard]] number_vec_ty provided() const {
            return m_provided;
        }

        [[nodiscard]] usize points() const {
            return m_points;
        }

        [[nodiscard]] usize number() const {
            return m_number;
        }

        [[nodiscard]] usize match_count() const {
            usize count{ };

            for (auto const &p : m_provided) {
                if (m_winning.contains(p)) {
                    count += 1;
                }
            }

            return count;
        }

        void double_points() {
            if (m_points == 0) {
                m_points = 1;
                return;
            }
            m_points *= 2;
        }

        void debug_print() const {
            hlp::print(hlp::PrintType::DEBUG, "Card {}", m_number);
            hlp::print(hlp::PrintType::DEBUG, "\twinning:");
            for (auto const &n : m_winning) {
                hlp::print(hlp::PrintType::DEBUG, "\t\t{}", n);
            }
            hlp::print(hlp::PrintType::DEBUG, "\tprovided:");
            for (auto const &n : m_provided) {
                hlp::print(hlp::PrintType::DEBUG, "\t\t{}", n);
            }
        }
    };

    [[nodiscard]] static inline std::set<usize> parse_number(std::string &numbers_s) {
        std::set<usize> result{ };

        hlp::trim(numbers_s);
        if (numbers_s.empty()) {
            hlp::print(hlp::PrintType::ERROR, "empty string while parsing numbers");
            return result;
        }
        auto numbers{ hlp::split(std::stringstream{ numbers_s }, ' ') };

        for (auto &n : numbers) {
            hlp::trim(n);
            if (n.empty()) {
                continue;
            }
            try {
                result.insert(std::stoi(n));
            } catch (std::invalid_argument const &) {
                hlp::print(hlp::PrintType::ERROR, "not able to parse string into number:  {}", n);
                continue;
            }
            catch (std::out_of_range const &) {
                hlp::print(hlp::PrintType::ERROR, "not able to parse string into number:  {}", n);
                continue;
            }
        }

        return result;
    }

    [[nodiscard]] static inline std::vector<Card> parse(std::string const &input) {
        std::vector<Card> result{ };

        std::stringstream ss{ input };
        std::string line{ };
        while (std::getline(ss, line)) {
            if (line.empty()) {
                hlp::print(hlp::PrintType::ERROR, "empty row while parsing cards");
                continue;
            }

            hlp::trim(line);
            auto all_numbers{ hlp::split(std::stringstream{ line }, ':') };
            if (all_numbers.size() != 2) {
                hlp::print(hlp::PrintType::ERROR, "unexpected spit count while splitting at ':'");
                continue;
            }

            hlp::trim(all_numbers[0]);
            auto card{ hlp::split(std::stringstream{ all_numbers[0] }, ' ') };
            if (all_numbers.size() != 2) {
                hlp::print(hlp::PrintType::ERROR, "unexpected spit count while splitting at ' '");
                continue;
            }

            hlp::trim(all_numbers[1]);
            auto numbers{ hlp::split(std::stringstream{ all_numbers[1] }, '|') };
            if (all_numbers.size() != 2) {
                hlp::print(hlp::PrintType::ERROR, "unexpected spit count while splitting at '|'");
                continue;
            }

            auto const number{ parse_number(card[card.size() - 1]) };
            auto const winning{ parse_number(numbers[0]) };
            auto const provided{ parse_number(numbers[1]) };
            auto const num_ptr{ number.begin() };

            result.emplace_back(*num_ptr, winning, provided);
        }

        return result;
    }

    [[nodiscard]] usize calculate_points(std::vector<Card> const &cards) {
        auto cards_mut = const_cast<std::vector<Card> &>(cards);
        usize result{ };

        for (auto &c : cards_mut) {
            for (auto const &provided : c.provided()) {
                if (c.winning().contains(provided)) {
                    c.double_points();
                }
            }
            result += c.points();
        }
        return result;
    }

    [[nodiscard]] usize copy_cards(std::vector<Card> const &cards) {
        std::unordered_map<usize, usize> card_counds{ };
        for (auto const &c : cards) {
            card_counds.insert({ c.number(), usize{ 1 }});
        }

        for (auto const &c : cards) {
            auto const count{ c.match_count() };
            for (usize n = c.number() + 1; n <= c.number() + count; ++n) {
                if (card_counds.contains(n)) {
                    card_counds[n] += card_counds[c.number()];
                }
            }
        }

        usize count{ 0 };
        for (auto const [key, value] : card_counds) {
            count += value;
        }
        return count;
    }


    void day_23_04() {
        // test 1
        hlp::print(hlp::PrintType::TEST_1, "Day 4: Scratchcards");

        auto const input_test_1{ hlp::load(directory + "test1.txt") };
        auto const cards_test_1{ parse(input_test_1) };
        auto const points_test_1{ calculate_points(cards_test_1) };

        hlp::compare_and_print(usize{ 13 }, points_test_1);

        // test 2
        hlp::print(hlp::PrintType::TEST_2, "Day 4: Scratchcards");

        auto const input_test_2{ hlp::load(directory + "test2.txt") };
        auto const card_test_2{ parse(input_test_2) };
        auto const count_test_2{ copy_cards(card_test_2) };

        hlp::compare_and_print(usize{ 30 }, count_test_2);

        // task
        hlp::print(hlp::PrintType::TASK, "Day 4: Scratchcards");

        auto const input{ hlp::load(directory + "input.txt") };
        auto const cards{ parse(input) };
        auto const points{ calculate_points(cards) };
        auto const count{ copy_cards(cards) };

        hlp::print(hlp::PrintType::RESULT, "count of all points in all cards: {}", points);
        hlp::print(hlp::PrintType::RESULT, "count of all cards after copy: {}", count);
    }
}
