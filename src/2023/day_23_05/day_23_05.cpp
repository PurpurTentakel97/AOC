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
#include <limits>

namespace d_23_05 {
    static const inline std::string title{ "Day 5: If You Give A Seed A Fertilizer" };
    static const inline std::string directory{ R"(src\2023\input_23\day_23_05\)" };

    struct Seed final {
        usize seed, soil, fertilizer, water, light, temperature, humidity;
        usize location{ };

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
                : destination{ 0 }, origin{ 0 }, range{ 0 } {
            assert(entries.size() == 3);
            destination = entries[0];
            origin = entries[1];
            range = entries[2];
        }
    };

    class Map final {
    private:
        std::vector<MapEntry> entries{ };
    public:

        void add_entry(MapEntry entry) {
            entries.push_back(entry);
        }

        [[nodiscard]] bool empty() const {
            return entries.empty();
        }

        [[nodiscard]] usize lookup(usize n) const {
            for (auto const &e : entries) {
                if (e.in_origin_range(n)) {
                    auto const offset = n - e.origin;
                    return e.destination + offset;
                }
            }
            return n;
        }
    };

    struct InputData final {
        std::vector<Map> maps;
        std::vector<Seed> seeds;
    };

    [[nodiscard]] static inline std::vector<Seed> parse_seeds(std::string const &s) {
        auto const numbers{ hlp::split(std::stringstream{ s }, ' ') };
        std::vector<Seed> seeds{ };

        for (auto const &ch : numbers) {
            if (hlp::is_multiple_digit(ch)) {
                auto seed = Seed{ };
                std::stringstream ss{ };
                ss << ch;
                usize num{ };
                ss >> num;
                seed.seed = num;
                seeds.push_back(seed);
            }
        }
        return seeds;
    }

    [[nodiscard]] static inline std::vector<Map> parse_maps(std::vector<std::string> &lines) {
        std::vector<Map> maps{ };
        Map map{ };

        auto const new_map{ [](std::vector<Map> &maps, Map &map) {
            if (map.empty()) {
                return;
            }
            maps.push_back(map);
            map = Map{ };
        }};

        for (auto &line : lines | std::ranges::views::drop(1)) {
            hlp::trim(line);

            if (line.empty()) {
                continue;
            }

            std::vector<usize> entries{ };
            auto const numbers{ hlp::split(std::stringstream{ line }, ' ') };
            for (auto const &number : numbers) {
                if (not hlp::is_multiple_digit(number)) {
                    new_map(maps, map);
                    break;
                }

                std::stringstream ss{ };
                ss << number;
                usize num{ };
                ss >> num;
                entries.push_back(num);
            }

            if (not entries.empty()) {
                auto entry = MapEntry(entries);
                map.add_entry(entry);
            }
        }

        new_map(maps, map);
        return maps;
    }

    [[nodiscard]] static inline InputData parse(std::string const &s) {
        auto lines{ hlp::split(std::stringstream{ s }, '\n') };
        auto const seeds{ parse_seeds(lines[0]) };
        auto const maps{ parse_maps(lines) };
        return { maps, seeds };
    }

    [[nodiscard]] static inline std::vector<Seed> map_seeds(InputData const &input) {
        std::vector<Seed> seeds{ input.seeds };

        assert(not seeds.empty());

        auto const &look_up{ [input](usize &origin, usize &destination, Map const &map) {
            destination = map.lookup(origin);
        }};

        for (auto &seed : seeds) {
            // @formatter:off
        look_up(seed.seed,        seed.soil,        input.maps[0]);
        look_up(seed.soil,        seed.fertilizer,  input.maps[1]);
        look_up(seed.fertilizer,  seed.water,       input.maps[2]);
        look_up(seed.water,       seed.light,       input.maps[3]);
        look_up(seed.light,       seed.temperature, input.maps[4]);
        look_up(seed.temperature, seed.humidity,    input.maps[5]);
        look_up(seed.humidity,    seed.location,    input.maps[6]);
        // @formatter:on
        }

        return seeds;
    }

    [[nodiscard]] static inline Seed lowest_seed(std::vector<Seed> const &seeds) {
        Seed lowest{ };
        lowest.location = std::numeric_limits<usize>::max();

        for (auto const &seed : seeds) {
            if (seed.location < lowest.location) {
                lowest = seed;
            }
        }
        return lowest;
    }

    void day_23_05() {
        using namespace hlp;
        // test 1
        print(PrintType::TEST_1, title);

        auto const input_test_1{ load(directory + "test1.txt") };
        auto const data_test_1{ parse(input_test_1) };
        auto const seeds_test_1{ map_seeds(data_test_1) };
        auto const lowest_location_test_1{ lowest_seed(seeds_test_1) };

        compare_and_print(usize{ 35 }, lowest_location_test_1.location);

        // test2
        print(PrintType::TEST_2, "not able to solve");

        // task
        print(PrintType::TASK, title);

        auto const input{ load(directory + "input.txt") };
        auto const data{ parse(input) };
        auto const seeds{ map_seeds(data) };
        auto const lowest_location{ lowest_seed(seeds) };

        print(PrintType::RESULT, "the nearest location ist: {}", lowest_location.location);
    }
}
