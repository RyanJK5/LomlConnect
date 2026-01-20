#include <array>

#include "patterns/TestPattern.hpp"

namespace Loml {
	void TestPattern::DisplayImpl(LEDStrip& led) {
		constexpr static uint8_t full = 10;

		led.ClearTo(RgbColor{full, 0, 0});
		led.Show();
		if (!Delay(500)) {
			return;
		}
		led.ClearTo(RgbColor{0, full, 0});
		led.Show();
		if (!Delay(500)) {
			return;
		}
		led.ClearTo(RgbColor{0, 0, full});
		led.Show();
		if (!Delay(500)) {
			return;
		}
	}
}