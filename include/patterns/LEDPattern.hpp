#ifndef __LEDPattern_hpp__
#define __LEDPattern_hpp__

#include <atomic>
#include <NeoPixelBus.h>

namespace Loml {
    using LEDStrip = NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>;

    constexpr inline std::array RingLengths = {
        1,
        8,
        12,
        16,
        24,
        32
    };

    constexpr inline std::array RingStartPositions = [](){
        std::array<int32_t, RingLengths.size()> ret{};
        for (auto i = 1; i < ret.size(); i++) {
            ret.at(i) = ret.at(i - 1) + RingLengths.at(i - 1);
        }
        return ret;
    }();

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

    template <int ColorCount>
    constexpr auto Dimmed(const std::array<RgbColor, ColorCount>& colors, uint8_t dim) {
        std::array<RgbColor, ColorCount> ret{};
        for (auto i = 0; i < colors.size(); i++) {
            ret.at(i) = colors.at(i).Dim(dim);
        }
        return ret;
    }

    class LEDPattern {
    public:
        constexpr LEDPattern() = default;
        virtual ~LEDPattern() = default;

        void Interrupt();

        void Display(LEDStrip& led);
    protected:
        virtual void DisplayImpl(LEDStrip& led) = 0;
    
        [[nodiscard]] auto Delay(int64_t delayMs) -> bool;

        static void DimRange(LEDStrip& led, uint16_t start = 0, uint16_t length = 0);
        static void BrightenRange(LEDStrip& led, uint16_t start = 0, uint16_t length = 0);
    
        std::atomic<bool> mInterrupted = false;
    };
}

#endif