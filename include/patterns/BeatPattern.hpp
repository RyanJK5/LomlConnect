#ifndef __BeatPattern_hpp__
#define __BeatPattern_hpp__

#include "patterns/LEDPattern.hpp"
#include "patterns/Colors.hpp"

#include <array>

namespace Loml {
    template <int ColorCount>
    class BeatPattern : public LEDPattern {
    public:
        constexpr BeatPattern(const std::array<RgbColor, ColorCount>& colors);
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;    
    private:
        std::array<RgbColor, ColorCount> mColors;
        size_t mColorIndex = 0;
    };

    template <int ColorCount>
    constexpr BeatPattern<ColorCount>::BeatPattern(const std::array<RgbColor, ColorCount>& colors) 
        : mColors(colors)
    { }

    template <int ColorCount>
    void BeatPattern<ColorCount>::DisplayImpl(LEDStrip& led) {
		constexpr static auto maxBrightness = 40;

		const auto color = mColors.at(mColorIndex);
		for (auto i = 0; i <= maxBrightness; i++) {
			for (auto j = 0; j < RingLengths.size(); j++) {
				for (auto k = 0; k < RingLengths.at(j); k++) {
					led.SetPixelColor(k + RingStartPositions.at(j), color.Dim(i));
				}
				led.Show();
				if (!Delay(10)) {
					return;
				}
			}
		}
		if (!Delay(500)) {
			return;
		}
		for (auto i = 0; i <= maxBrightness; i++) {
			for (auto j = 0; j < RingLengths.size(); j++) {
				for (auto k = 0; k < RingLengths.at(j); k++) {
					led.SetPixelColor(k + RingStartPositions.at(j), color.Dim(maxBrightness - i));
				}
				led.Show();
				if (!Delay(10)) {
					return;
				}
			}
		}
		if (!Delay(500)) {
			return;
		}
		mColorIndex = (mColorIndex + 1) % mColors.size();
	}
}

#endif