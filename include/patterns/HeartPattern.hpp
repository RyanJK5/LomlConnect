#ifndef HeartPattern_hpp_
#define HeartPattern_hpp_

#include "patterns/LetterPattern.hpp"

#include <memory>

namespace Loml {
    template <typename Background>
    class HeartPattern : public LetterPattern {
    public:
		static_assert(std::is_base_of_v<BackgroundPattern, Background>);

        template <typename... Args>
        constexpr HeartPattern(RgbColor letterColor, Args&&... args)
            : LetterPattern(letterColor, 40, 100)
            , mBackground(true, std::forward<Args>(args)...)
        { }
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;
    private:
        Background mBackground;

    };

    template <typename Background>
    void HeartPattern<Background>::DisplayImpl(LEDStrip& led) {
		DisplayLetterPattern(
			led, mBackground,
			OrderedHeartPositions
		);
    }
}

#endif