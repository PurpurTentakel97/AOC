//
// Purpur Tentakel
// AOC 06/2023
//

#include "day_23_07.hpp"
#include "types.hpp"
#include "string.hpp"
#include "load.hpp"
#include "compare.hpp"

#include <string>
#include <unordered_map>
#include <array>
#include <cassert>
#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace d_23_07 {
    static inline const std::string title{ "Day 7: Camel Cards" };
    static inline const std::string directory{ R"(src\2023\input_23\day_23_07\{})" };

    enum class CardType {
        Default,
        HighCard,
        OnePair,
        TwoPair,
        Three,
        FullHouse,
        Four,
        Five,
    };

    static const inline std::unordered_map<CardType, std::string> type_string_lookup{
            // @formatter:off
            { CardType::Default,   "CardType::Default"   },
            { CardType::HighCard,  "CardType::HighCard"  },
            { CardType::OnePair,   "CardType::OnePair"   },
            { CardType::TwoPair,   "CardType::TwoPair"   },
            { CardType::Three,     "CardType::Three"     },
            { CardType::FullHouse, "CardType::FullHouse" },
            { CardType::Four,      "CardType::Four"      },
            { CardType::Five,      "CardType::Five"      },
            // @formatter:on
    };

    enum class HandCard {
        // @formatter:off
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
     T,
     J,
     Q,
     K,
     A,
    // @formatter:on
    };

    static const inline std::unordered_map<char, HandCard> char_hand_lookup{
            // @formatter:off
        { '2', HandCard::_2 },
        { '3', HandCard::_3 },
        { '4', HandCard::_4 },
        { '5', HandCard::_5 },
        { '6', HandCard::_6 },
        { '7', HandCard::_7 },
        { '8', HandCard::_8 },
        { '9', HandCard::_9 },
        { 'T', HandCard::T  },
        { 'J', HandCard::J  },
        { 'Q', HandCard::Q  },
        { 'K', HandCard::K  },
        { 'A', HandCard::A  },
    // @formatter:on
    };
    static const inline std::unordered_map<HandCard, char> hand_char_lookup{
            // @formatter:off
        { HandCard::_2, '2' },
        { HandCard::_3, '3' },
        { HandCard::_4, '4' },
        { HandCard::_5, '5' },
        { HandCard::_6, '6' },
        { HandCard::_7, '7' },
        { HandCard::_8, '8' },
        { HandCard::_9, '9' },
        { HandCard::T , 'T' },
        { HandCard::J , 'J' },
        { HandCard::Q , 'Q' },
        { HandCard::K , 'K' },
        { HandCard::A , 'A' },
        // @formatter:on
    };

    using Hand = std::array<HandCard, 5>;

    static inline std::string hand_to_string(Hand const &hand) {
        return hlp::str("{}{}{}{}{}",
                        hand_char_lookup.at(hand[0]),
                        hand_char_lookup.at(hand[1]),
                        hand_char_lookup.at(hand[2]),
                        hand_char_lookup.at(hand[3]),
                        hand_char_lookup.at(hand[4])
        );
    }

    static constexpr inline Hand lookup_cards(std::string const &input) {
        assert(input.size() == 5);
        std::array<HandCard, 5> result{ };

        for (int i = 0; i < input.size(); ++i) {
            if (not char_hand_lookup.contains(input[i])) {
                throw std::runtime_error{ hlp::str("hand lookup does not contain '{}'", input[i]) };
            }
            result[i] = char_hand_lookup.at(input[i]);
        }

        return result;
    }

    static inline CardType define_card_type(std::array<HandCard, 5> const &hand) {
        std::unordered_map<HandCard, usize> cards{ };
        for (auto const &h : hand) {
            if (not cards.contains(h)) {
                cards[h] = 1;
            } else {
                ++cards[h];
            }
        }

        switch (cards.size()) {
            case 1:
                return CardType::Five;
            case 2:
                for (auto const &[type, count] : cards) {
                    if (count == 4) {
                        return CardType::Four;
                    }
                }
                return CardType::FullHouse;
            case 3:
                for (auto const &[type, count] : cards) {
                    if (count == 3) {
                        return CardType::Three;
                    }
                }
                return CardType::TwoPair;
            case 4:
                return CardType::OnePair;
            case 5:
                return CardType::HighCard;
        }
        throw std::runtime_error{ hlp::str("no card_type found: {}", hand_to_string(hand)) };
    }

    struct Card final {
        usize bid;
        std::string hand_s;
        std::array<HandCard, 5> hand_a;
        CardType type{ CardType::Default };

        void print() const {
            hlp::print(hlp::PrintType::DEBUG,
                       "Card: bid: {} | hand_s: {} | hand_a: {} | type: {}",
                       bid,
                       hand_s,
                       hand_to_string(hand_a),
                       type_string_lookup.at(type)
            );
        }
    };

    static inline std::vector<Card> parse(std::string const &input) {
        std::vector<Card> cards{ };
        std::stringstream ss{ input };
        std::string out{ };

        while (std::getline(ss, out)) {
            hlp::trim(out);
            if (out.empty()) {
                continue;
            }

            auto i{ hlp::split(std::stringstream{ out }, ' ') };
            assert(i.size() == 2);
            hlp::trim(i[0]);
            hlp::trim(i[1]);
            if (not hlp::is_multiple_digit(i[1])) {
                throw std::runtime_error{ hlp::str("error parsing number: '{}' is no number", i[2]) };
            }

            std::stringstream s{ i[1] };
            usize value;
            s >> value;

            auto const hand{ lookup_cards(i[0]) };

            cards.emplace_back(
                    value,
                    i[0],
                    hand,
                    define_card_type(hand)
            );
        }
        return cards;
    }

    static void sort_cards(std::vector<Card> &cards) {
        auto const rule{ [](Card const &lhs, Card const &rhs) -> bool {
            if (lhs.type != rhs.type){
                return lhs.type < rhs.type;
            }
            assert(lhs.hand_a.size() == 5);
            assert(rhs.hand_a.size() == 5);
            for (usize i = 0; i < lhs.hand_a.size(); ++i){
                if (lhs.hand_a[i] != rhs.hand_a[i]){
                    return lhs.hand_a[i] < rhs.hand_a[i];
                }
            }
            throw std::runtime_error{"same card"};
        }};
        std::sort(cards.begin(), cards.end(), rule);
    }

    static usize multiply(std::vector<Card> const &cards) {
        usize count{ };
        for (usize i = 0; i < cards.size(); ++i) {
            count += (i + 1) * cards[i].bid;
        }
        return count;
    }

    void day_23_07() {
        using namespace hlp;

        // test 1
        print(PrintType::TEST_1, title);

        auto const input_test_1{ load(str(directory, "test1.txt")) };
        auto cards_test_1{ parse(input_test_1) };
        sort_cards(cards_test_1);
        auto const count_test_1{ multiply(cards_test_1) };

        compare_and_print(usize{ 6440 }, count_test_1);

        // task
        print(PrintType::TASK, title);

        auto const input{load(str(directory,"input.txt"))};
        auto cards{ parse(input)};
        sort_cards(cards);
        auto const count{ multiply(cards)};

        print(PrintType::RESULT, "the total winnings are: {}", count);
    }
}
