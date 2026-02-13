#ifndef LetterPattern_hpp_
#define LetterPattern_hpp_

#include "patterns/LEDPattern.hpp"
#include "patterns/BackgroundPattern.hpp"

namespace Loml {
    class LetterPattern : public LEDPattern {
    public:
        constexpr LetterPattern(RgbColor letterColor, int64_t letterDelay, int64_t patternDelay)
			: mLetterColor(letterColor)
			, mLetterDelay(letterDelay)
			, mPatternDelay(patternDelay)
		{ }

        virtual ~LetterPattern() = default;
    protected:
        template <typename... Args>
        void DisplayLetterPattern(LEDStrip& led, BackgroundPattern& bg, Args&&... arrays) {
			const auto showPartOfLetter = [&](const auto& letter, int32_t index) {
				for (int k = 0; k < mPatternDelay; k += mLetterDelay) {
					bg.Display(led);
					for (auto j = 0; j <= index; j++) {
						led.SetPixelColor(letter[j], mLetterColor.Dim(20));
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
			
			const auto args_tuple = std::forward_as_tuple(arrays...);
			const auto& lastArray = std::get<sizeof...(Args) - 1>(args_tuple);

			for (int32_t i = lastArray.size() - 1; i >= 0; i--) {
				if (!showPartOfLetter(lastArray, i)) {
					return;
				}
			}
		}
	private:
		RgbColor mLetterColor;
		int64_t mLetterDelay;
		int64_t mPatternDelay;
    };
    
}

#endif