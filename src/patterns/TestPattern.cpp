#include <array>

#include "patterns/TestPattern.hpp"

namespace Loml {
	TestPattern::TestPattern() 
		: LEDPattern(500)
	{ }
	
	void TestPattern::Display(LEDStrip& led) {
		constexpr static uint8_t full = 10;
		constexpr static uint8_t zero = 0;

		RgbColor color{
			mColorIndex == 0 ? full : zero,
			mColorIndex == 1 ? full : zero,
			mColorIndex == 2 ? full : zero
		};
		mColorIndex = (mColorIndex + 1) % 3;
	
		led.ClearTo(color);
		led.Show();
	}
}