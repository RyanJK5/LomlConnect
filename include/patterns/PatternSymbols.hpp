#ifndef PatternSymbols_hpp_
#define PatternSymbols_hpp_

#include <array>
#include <numeric>
#include <vector>

namespace Loml {
    // The lengths of each ring in the LED board.
    constexpr inline std::array RingLengths = {
        1,
        8,
        12,
        16,
        24,
        32
    };

    // The index of the first pixel in each ring of the LED board.
    constexpr inline std::array RingStartPositions = [](){
        std::array<int32_t, RingLengths.size()> ret{};
        for (auto i = 1; i < ret.size(); i++) {
            ret.at(i) = ret.at(i - 1) + RingLengths.at(i - 1);
        }
        return ret;
    }();

    // The horizontal levels of the LED board. It's approximate, and will look best if 
    // some kind of gradient is applied rather than turning each level on individually.
    // Note that this could be available at compile time as a std::tuple, but for simplicity
    // I just opted to place it in static storage.
    inline std::array Levels = {
        std::vector { 70, 71, 72, 73, 74, 75, 76 },
        std::vector { 69, 44, 45, 46, 47, 48, 77 },
        std::vector { 68, 43, 26, 27, 28, 49, 78 },
        std::vector { 67, 42, 25, 13, 14, 29, 50, 79 },
        std::vector { 66, 41, 24, 12, 15, 30, 51, 80 },
        std::vector { 11, 3, 4, 5, 16 },
        std::vector { 65, 40, 23, 2, 0, 6, 31, 52, 81 },
        std::vector { 10, 1, 7, 17 },
        std::vector { 64, 39, 22, 9, 8, 18, 32, 53, 82 },
        std::vector { 63, 38, 21, 20, 19, 33, 54, 83 },
        std::vector { 62, 37, 36, 35, 34, 55, 84 },
        std::vector { 61, 60, 56, 85 },
        std::vector { 92, 59, 58, 57, 86 },
        std::vector { 91, 90, 89, 88, 87 }
    };

    // Array of every position in order, grouped by rings. All of the innermost ring's pixels
    // are in RingLevels[0], etc.
    inline std::array RingLevels = [](){
        std::array<std::vector<int32_t>, RingLengths.size()> ret{};

        for (auto i = 0; i < ret.size(); i++) {
            ret[i].resize(RingLengths[i]);
            std::iota(ret[i].begin(), ret[i].end(), RingStartPositions[i]);
        }

        return ret;
    }();

    // Positions for displaying an L-shape from the top to the bottom.
    constexpr inline std::array OrderedLPositions {
        26, 12, 11, 10, 21, 20, 19, 33
    };

    // Positions for display the letter O, which is just the second ring.
    constexpr inline std::array OrderedOPositions = [](){
        std::array<int32_t, RingLengths[2]> ret{};
        for (auto i = 0; i < RingLengths[2]; i++) {
            ret[i] = RingStartPositions[2] + i;
        }
        return ret;
    }();

    // Positions for displaying an M-shape from bottom left to bottom right.
    constexpr inline std::array OrderedMPositions {
        21, 10, 11, 12, 26, 13, 4, 14, 28, 15, 16, 17, 33
    };

    // Positions for showing the first cross of an X, then the second.
    constexpr inline std::array OrderedXPositions {
        25, 12, 3, 0, 7, 18, 33,
        29, 15, 5, 0, 1, 9, 21
    };

    // Positions for showing the inside of a heart and swirling it out into the whole shape.
    constexpr inline std::array OrderedHeartPositions {
        0, 5, 6, 7, 8, 1, 2, 3, 15, 16, 17, 18, 19, 35, 20, 9, 10, 11, 12
    };
}

#endif