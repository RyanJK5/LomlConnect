#ifndef __XOPattern_hpp__
#define __XOPattern_hpp__

#include "patterns/LetterPattern.hpp"

namespace Loml {
    template <typename Background>
    class LomlPattern : public LetterPattern {
    public:
		static_assert(std::is_base_of_v<BackgroundLEDPattern, Background>);

        template <typename... Args>
        constexpr LomlPattern(Args&&... args)
            : mBackground(true, std::forward<Args>(args)...)
        { }
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;
    private:
        Background mBackground;
    };

    template <typename Background>
    void LomlPattern<Background>::DisplayImpl(LEDStrip& led) {
        LetterPattern::DisplayLetterPattern(led, mBackground, OrderedXPositions, OrderedOPositions);
    }
}

#endif