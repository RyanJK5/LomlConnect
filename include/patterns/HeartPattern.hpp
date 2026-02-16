#ifndef HeartPattern_hpp_
#define HeartPattern_hpp_

#include "patterns/LetterPattern.hpp"

#include <memory>

namespace Loml {
    // Display a heart, with the templated pattern shown in the background.
    template <typename Background>
    class HeartPattern : public LetterPattern {
    public:
		static_assert(std::is_base_of_v<BackgroundPattern, Background>); // Could be made cleaner with C++ 20 concepts

        // Pass in the color of the heart, and then the various params for the background pattern.
        template <typename... Args>
        constexpr HeartPattern(RgbColor letterColor, Args&&... args)
            : LetterPattern(letterColor, 40, 100)
            , mBackground(true, std::forward<Args>(args)...)
        { }
    protected:
        void DisplayImpl(LEDStrip& led) override final;
    private:
        Background mBackground;

    };

    template <typename Background>
    void HeartPattern<Background>::DisplayImpl(LEDStrip& led) {
		DisplayLetterPattern(
			led, mBackground,
			OrderedHeartPositions // Ordered in such a way that the heart spirals from the inside out
		);
    }
}

#endif