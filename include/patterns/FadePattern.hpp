#ifndef __FadePattern_h__
#define __FadePattern_h__

#include <patterns/BackgroundLEDPattern.hpp>

namespace Loml {
    class FadePattern : public BackgroundLEDPattern {
    public:
        constexpr FadePattern(bool inBackground, RgbColor left, RgbColor right);
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;
    private:
        RgbColor mLeft;
        RgbColor mRight;

        int32_t mColorCounter = 0;
    };

    constexpr FadePattern::FadePattern(bool inBackground, RgbColor left, RgbColor right) 
        : BackgroundLEDPattern(inBackground)
        , mLeft(left)
        , mRight(right)
    { }
}

#endif