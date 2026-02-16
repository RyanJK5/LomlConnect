#ifndef LomlPattern_hpp_
#define LomlPattern_hpp_

#include "patterns/LetterPattern.hpp"

#include <memory>

namespace Loml {
    template <typename Background>
    class LomlPattern : public LetterPattern {
    public:
		static_assert(std::is_base_of_v<BackgroundPattern, Background>);

        template <typename... Args>
        constexpr LomlPattern(RgbColor letterColor, Args&&... args)
            : LetterPattern(letterColor, 40, 100)
            , mBackground(true, std::forward<Args>(args)...)
        { }
    protected:
        void DisplayImpl(LEDStrip& led) override final;
    private:
        Background mBackground;

    };

    template <typename Background>
    void LomlPattern<Background>::DisplayImpl(LEDStrip& led) {
		DisplayLetterPattern(
			led, mBackground,
			OrderedLPositions, 
			OrderedOPositions, 
			OrderedMPositions,
			OrderedLPositions
		);
    }
}

#endif