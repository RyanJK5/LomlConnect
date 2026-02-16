#ifndef XOPattern_hpp_
#define XOPattern_hpp_

#include "patterns/LetterPattern.hpp"

namespace Loml {
    template <typename Background>
    class XOPattern : public LetterPattern {
    public:
		static_assert(std::is_base_of_v<BackgroundPattern, Background>);

        template <typename... Args>
        constexpr XOPattern(RgbColor letterColor, Args&&... args)
            : LetterPattern(letterColor, 20, 50)
            , mBackground(true, std::forward<Args>(args)...)
        { }
    protected:
        void DisplayImpl(LEDStrip& led) override final;
    private:
        Background mBackground;
    };

    template <typename Background>
    void XOPattern<Background>::DisplayImpl(LEDStrip& led) {
        DisplayLetterPattern(led, mBackground,
            OrderedXPositions, OrderedOPositions,
            OrderedXPositions, OrderedOPositions // Show XO twice so that we only show the letter collapsing on the second 'O'
        );
    }
}

#endif