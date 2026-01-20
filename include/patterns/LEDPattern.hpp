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

    class LEDPattern {
    public:
        constexpr LEDPattern() = default;
        virtual ~LEDPattern() = default;

        void Interrupt();

        void Display(LEDStrip& led);
    protected:
        virtual void DisplayImpl(LEDStrip& led) = 0;
    
        [[nodiscard]] auto Delay(int64_t delayMs) -> bool;

        static void DimAll(LEDStrip& led);
        static void BrightenAll(LEDStrip& led);
    private:
        std::atomic<bool> mInterrupted = false;
    };
}

#endif