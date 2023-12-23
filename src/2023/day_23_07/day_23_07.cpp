//
// Purpur Tentakel
// AOC 06/2023
//

#include "day_23_07.hpp"
#include "types.hpp"
#include "string.hpp"
#include "load.hpp"

#include <string>
#include <unordered_map>
#include <array>
#include <cassert>
#include <stdexcept>
#include <sstream>

static inline const std::string title{ "Day 7: Camel Cards" };
static inline const std::string directory{ R"(src\2023\input_23\day_23_07\{})" };

enum class CardType {
    HighCard,
    OnePair,
    TwoPair,
    Three,
    FullHouse,
    Four,
    Five,
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

static constexpr inline std::array<HandCard, 5> lookup_cards(std::string const &input) {
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

struct Card final {
    usize bid;
    std::string hand_s;
    std::array<HandCard, 5> hand_a;

    void print() const {
        hlp::print(hlp::PrintType::DEBUG,
                   "Card: bid: {} | hand_s: {} | hand_a: {}{}{}{}{}",
                   bid,
                   hand_s,
                   hand_char_lookup.at(hand_a[0]),
                   hand_char_lookup.at(hand_a[1]),
                   hand_char_lookup.at(hand_a[2]),
                   hand_char_lookup.at(hand_a[3]),
                   hand_char_lookup.at(hand_a[4])
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
            std::runtime_error{ hlp::str("error parsing number: '{}' is no number", i[2]) };
        }

        hlp::print(hlp::PrintType::DEBUG, "bid: {}", std::stoi(i[1]));
        hlp::print(hlp::PrintType::DEBUG, "hand_s: {}", i[0]);
        auto const e{ lookup_cards(i[0]) };
        hlp::print(hlp::PrintType::DEBUG, "hand_a: {}{}{}{}{}",
                   hand_char_lookup.at(e[0]),
                   hand_char_lookup.at(e[1]),
                   hand_char_lookup.at(e[2]),
                   hand_char_lookup.at(e[3]),
                   hand_char_lookup.at(e[4])
        );

        std::stringstream s{ i[1] };
        usize value;
        s >> value;

        Card const card{
                value,
                i[0],
                lookup_cards(i[0])
        };

        cards.push_back(card);
    }
    return cards;
}


void day_23_07() {
    using namespace hlp;

    // test 1
    auto const input_test_1{ load(str(directory, "test1.txt")) };
    auto const cards_test_1{ parse(input_test_1) };

    for (auto const &c : cards_test_1) {
        // c.print();
    }

}
