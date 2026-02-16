#ifndef BeatPattern_hpp_
#define BeatPattern_hpp_

#include "patterns/LEDPattern.hpp"
#include "patterns/Colors.hpp"

#include <array>

namespace Loml {
	// A pattern that pulses between multiple different colors.
    template <int ColorCount> // The number of different colors to pulse between
    class BeatPattern : public LEDPattern {
    public:
        constexpr BeatPattern(
			const std::array<RgbColor, ColorCount>& colors, 
			int64_t delayTimeMs = 30, // The delay between each step in increasing the color's brightness
			int64_t holdTimeMs = 500 // How long a color should be held at max brightness
		);
    protected:
        void DisplayImpl(LEDStrip& led) override final;    
    private:
        std::array<RgbColor, ColorCount> mColors;
        size_t mColorIndex = 0;

		int64_t mDelayTimeMs;
		int64_t mHoldTimeMs;
    };

    template <int ColorCount>
    constexpr BeatPattern<ColorCount>::BeatPattern(
			const std::array<RgbColor, ColorCount>& colors,
			int64_t delayTimeMs, 
			int64_t holdTimeMs)
        : mColors(colors)
		, mDelayTimeMs(delayTimeMs)
		, mHoldTimeMs(holdTimeMs)
    { }

    template <int ColorCount>
    void BeatPattern<ColorCount>::DisplayImpl(LEDStrip& led) {
		constexpr static auto maxBrightness = 10;

		const auto color = mColors.at(mColorIndex);
		for (auto i = 0; i <= maxBrightness; i++) {
			for (auto j = 0; j < RingLengths.size(); j++) {
				for (auto k = 0; k < RingLengths.at(j); k++) {
					led.SetPixelColor(k + RingStartPositions.at(j), color.Dim(i));
				}
				led.Show();
				if (!Delay(mDelayTimeMs)) {
					return;
				}
			}
		}

		if (!Delay(mHoldTimeMs)) {
			return;
		}
		
		for (auto i = 0; i <= maxBrightness; i++) {
			for (auto j = 0; j < RingLengths.size(); j++) {
				for (auto k = 0; k < RingLengths.at(j); k++) {
					led.SetPixelColor(k + RingStartPositions.at(j), color.Dim(maxBrightness - i));
				}
				led.Show();
				if (!Delay(mDelayTimeMs)) {
					return;
				}
			}
		}
		
		if (!Delay(mHoldTimeMs)) {
			return;
		}
		mColorIndex = (mColorIndex + 1) % mColors.size();
	}
}

#endif