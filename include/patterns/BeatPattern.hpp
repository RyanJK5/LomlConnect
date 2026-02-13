#ifndef BeatPattern_hpp_
#define BeatPattern_hpp_

#include "patterns/LEDPattern.hpp"
#include "patterns/Colors.hpp"

#include <array>

namespace Loml {
    template <int ColorCount>
    class BeatPattern : public LEDPattern {
    public:
        constexpr BeatPattern(
			const std::array<RgbColor, ColorCount>& colors, 
			int64_t delayTimeMs = 30, 
			int64_t holdTimeMs = 500
		);
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;    
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