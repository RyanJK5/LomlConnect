#ifndef __LEDPattern_hpp__
#define __LEDPattern_hpp__

#include <atomic>
#include <NeoPixelBus.h>

#include "patterns/PatternSymbols.hpp"

namespace Loml {
    using LEDStrip = NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>;

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
    private:
        std::atomic<bool> mInterrupted = false;
    };
}

#endif