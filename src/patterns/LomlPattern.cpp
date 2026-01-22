#include <array>
#include <numeric>

#include "patterns/LomlPattern.hpp"
#include "patterns/FadePattern.hpp"
#include "patterns/Colors.hpp"

namespace Loml {
	void LomlPattern::DisplayImpl(LEDStrip& led) {
		constexpr static std::array orderedLPositions {
			26, 12, 11, 10, 21, 20, 19, 33
		};

		constexpr static std::array orderedOPositions = [](){
			std::array<int32_t, RingLengths[2]> ret{};
			for (auto i = 0; i < RingLengths[2]; i++) {
				ret[i] = RingStartPositions[2] + i;
			}
			return ret;
		}();
		
		constexpr static std::array orderedMPositions {
			21, 10, 11, 12, 26, 13, 4, 14, 28, 15, 16, 17, 33
		};

		FadePattern background{Colors::Blue, Colors::Purple, true};

		const auto showPartOfLetter = [&](const auto& letter, int32_t index) {
			for (int k = 0; k < 100; k += 20) {
				background.Display(led);
				for (auto j = 0; j <= index; j++) {
					led.SetPixelColor(letter[j], Colors::Red.Dim(20));
				}
				led.Show();

				if (!Delay(20)) {
					return false;
				}
			}
			return true;
		};

		const auto hold = [&](const auto& letter, int32_t amount) {
			for (auto i = 0; i < 6; i++) {
				if (!showPartOfLetter(letter, amount)) {
					return false;
				}
			}
			return true;
		};

		const auto showLetter = [&](const auto& letter) {
			for (auto i = 0; i < letter.size(); i++) {
				if (!showPartOfLetter(letter, i)) {
					return false;
				}
			}
			return hold(letter, letter.size() - 1);
		};

		if (!hold(orderedLPositions, -1)) {
			return;
		}
		if (!showLetter(orderedLPositions)) {
			return;
		}
		if (!showLetter(orderedOPositions)) {
			return;
		}
		if (!showLetter(orderedMPositions)) {
			return;
		}
		if (!showLetter(orderedLPositions)) {
			return;
		}
		
		for (int32_t i = orderedLPositions.size() - 1; i >= 0; i--) {
			if (!showPartOfLetter(orderedLPositions, i)) {
				return;
			}
		}
	}
}