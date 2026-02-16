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
        template <typename... Args> // Parameter pack contains each letter that should be displayed in sequence
        void DisplayLetterPattern(LEDStrip& led, BackgroundPattern& bg, Args&&... arrays) {
			// Show the letter from [0..index]
			const auto showPartOfLetter = [&](const auto& letter, int32_t index) {
				for (int k = 0; k < mPatternDelay; k += mLetterDelay) {
					[[maybe_unused]] const auto expired = bg.Display(led); // Assume bg has no lifetime
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

			// Holds a letter in place for 6 ticks, while still updating the background.
			const auto hold = [&](const auto& letter, int32_t amount) {
				for (auto i = 0; i < 6; i++) {
					if (!showPartOfLetter(letter, amount)) {
						return false;
					}
				}
				return true;
			};

			// Shows each part of a letter one by one, then holds it.
			const auto showLetter = [&](const auto& letter) {
				for (auto i = 0; i < letter.size(); i++) {
					if (!showPartOfLetter(letter, i)) {
						return false;
					}
				}
				return hold(letter, letter.size() - 1);
			};

			// Weird way of writing "show just the background for 6 ticks"
			if (!hold(std::array<int, 1>{ 0 }, -1)) {
				return;
			}

			// Fold expression: we iterate over each of the provided letters and display them in order.
			// Folding over && causes us to return early if an interrupt is called.
			if (!(showLetter(std::forward<Args>(arrays)) && ...)) {
				return;
			}
			
			const auto args_tuple = std::forward_as_tuple(arrays...);
			const auto& lastArray = std::get<sizeof...(Args) - 1>(args_tuple);
			// For the last letter, we remove a piece of it until the whole thing is hidden.
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