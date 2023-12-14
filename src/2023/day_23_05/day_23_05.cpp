//
// Purpur Tentakel
// AOC 05/2023
//

#include "day_23_05.hpp"
#include "print.hpp"
#include "load.hpp"
#include "string.hpp"
#include "compare.hpp"
#include "types.hpp"
#include <sstream>
#include <cassert>
#include <ranges>

static const inline std::string title{"Day 5: If You Give A Seed A Fertilizer"};
static const inline std::string directory{R"(src\2023\input_23\day_23_05\)"};

struct Seed final {
    usize seed, soil, fertilizer, water, light, temperature, humidity, location;

    void print() const {
        hlp::print(hlp::PrintType::DEBUG, "Seed:");
        hlp::print(hlp::PrintType::NONE, "seed:{}", seed);
        hlp::print(hlp::PrintType::NONE, "soil:{}", soil);
        hlp::print(hlp::PrintType::NONE, "fertilizer:{}", fertilizer);
        hlp::print(hlp::PrintType::NONE, "water:{}", water);
        hlp::print(hlp::PrintType::NONE, "light:{}", light);
        hlp::print(hlp::PrintType::NONE, "temperature:{}", temperature);
        hlp::print(hlp::PrintType::NONE, "humidity:{}", humidity);
        hlp::print(hlp::PrintType::NONE, "location:{}", location);
    }
};

struct MapEntry final {
    usize destination, origin, range;

    [[nodiscard]] bool in_origin_range(usize n) const {
        return origin <= n
               && origin + range >= n;
    }

    explicit MapEntry(std::vector<usize> const &entries)
            : destination{0}, origin{0}, range{0} {
        assert(entries.size() == 3);
        destination = entries[0];
        origin = entries[1];
        range = entries[2];
    }
};

class Map final {
private:
    std::vector<MapEntry> entries{};
public:

    void add_entry(MapEntry entry){
        entries.push_back(entry);
    }

    [[nodiscard]] bool empty() const {
        return entries.empty();
    }

    [[nodiscard]] usize lookup(usize n) const {
        for (auto const &e: entries) {
            if (e.in_origin_range(n)) {
                auto const offset = n - e.origin;
                return e.destination + offset;
            }
        }
    }
};

struct InputData final{
    std::vector<Map> maps;
    std::vector<Seed> seeds;
};

[[nodiscard]] static inline std::vector<Seed> parse_seeds(std::string const &s) {
    auto const numbers{hlp::split(std::stringstream{s}, ' ')};
    std::vector<Seed> seeds{};

    for (auto const &ch: numbers) {
        if (hlp::is_multiple_digit(ch)) {
            auto seed = Seed{};
            seed.seed = std::stoi(ch);
            seeds.push_back(seed);
        }
    }
    return seeds;
}

[[nodiscard]] static inline std::vector<Map> parse_maps(std::vector<std::string> &lines) {
    std::vector<Map> maps{};
    Map map{};

    auto const new_map{[](std::vector<Map> &maps, Map &map) {
        if (map.empty()) { return; }
        maps.push_back(map);
        map = Map{};
    }};

    for (auto &line: lines | std::ranges::views::drop(1)) {
        hlp::trim(line);

        if (line.empty()) { continue; }

        std::vector<usize> entries{};
        auto const numbers{hlp::split(std::stringstream{line}, ' ')};
        for (auto const &number: numbers) {
            if (not hlp::is_multiple_digit(number)) {
                new_map(maps, map);
                break;
            }

            entries.push_back(std::stoi(number));
        }

        if (not entries.empty()){
            auto entry = MapEntry(entries);
            map.add_entry(entry);
        }
    }

    new_map(maps, map);
    return maps;
}

[[nodiscard]] static inline InputData parse(std::string const &s) {
    auto lines{hlp::split(std::stringstream{s}, '\n')};
    auto const seeds{parse_seeds(lines[0])};
    auto const maps{parse_maps(lines)};
    return {maps, seeds};
}

void day_23_05() {
    using namespace hlp;
    print(PrintType::TEST_1, title);

    auto const input_test_1{load(directory + "test1.txt")};
    auto const data_test_1{parse(input_test_1)};

    compare_and_print(35, 0);
}
