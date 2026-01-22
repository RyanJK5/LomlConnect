#ifndef RadiatePattern_hpp_
#define RadiatePattern_hpp_

#include "patterns/LEDPattern.hpp"

namespace Loml {
    template <int ColorCount>
    class RadiatePattern : public LEDPattern {
    public:
        constexpr RadiatePattern(const std::array<RgbColor, ColorCount>& colors);
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;
    private:
        std::array<RgbColor, ColorCount> mColors;
    };

    template <int ColorCount>
    constexpr RadiatePattern<ColorCount>::RadiatePattern(const std::array<RgbColor, ColorCount>& colors) 
        : mColors(colors)
    { }

    template <int ColorCount>
    void RadiatePattern<ColorCount>::DisplayImpl(LEDStrip& led) {
        constexpr static auto colorBrightness = 30;

        const auto displayRing = [&](RgbColor color, int32_t index) {
            const auto startPos = RingStartPositions.at(index); 
            const auto endPos = startPos + RingLengths.at(index);

            for (auto j = startPos; j < endPos; j++) {
                led.SetPixelColor(j, color.Dim(colorBrightness));
            }
            led.Show();
        };

        for (auto color = 0; color < mColors.size(); color++) {
            for (auto i = 0; i < RingLengths.size() - color; i++) {
                displayRing(mColors[color], i);
                if (!Delay(50)) {
                    return;
                }
                if (i != RingLengths.size() - 1 - color) {
                    displayRing(Colors::Black, i);
                }

            }
        }
        if (!Delay(500)) {
            return;
        }

        for (auto i = RingLengths.size(); i > 0; i--) {
            for (auto j = 0; j < colorBrightness; j++) {
                DimRange(led, RingStartPositions.at(i - 1), RingLengths.at(i - 1));
                if (!Delay(10)) {
                    return;
                }
            }
        }
    }
}

#endif