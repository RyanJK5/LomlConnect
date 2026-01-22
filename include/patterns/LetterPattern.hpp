#ifndef __LetterPattern_hpp__
#define __LetterPattern_hpp__

#include "patterns/LEDPattern.hpp"
#include "patterns/BackgroundLEDPattern.hpp"

namespace Loml {
    class LetterPattern : public LEDPattern {
    public:
        constexpr LetterPattern() = default;
        virtual ~LetterPattern() = default;
    protected:
        template <typename... Args>
        void DisplayLetterPattern(LEDStrip& led, BackgroundLEDPattern& bg, Args&&... arrays) {
        const auto showPartOfLetter = [&](const auto& letter, int32_t index) {
			for (int k = 0; k < 100; k += 20) {
				bg.Display(led);
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

		if (!hold(std::array<int, 1>{ 0 }, -1)) {
			return;
		}

        if (!(showLetter(std::forward<Args>(arrays)) && ...)) {
            return;
        }
		
        auto args_tuple = std::forward_as_tuple(arrays...);
        const auto& lastArray = std::get<sizeof...(Args) - 1>(args_tuple);

        for (int32_t i = lastArray.size() - 1; i >= 0; i--) {
            if (!showPartOfLetter(lastArray, i)) {
                return;
            }
        }
    }
    };
    
}

#endif