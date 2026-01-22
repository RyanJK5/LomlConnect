#ifndef __FadePattern_h__
#define __FadePattern_h__

#include <patterns/LEDPattern.hpp>

namespace Loml {
    class FadePattern : public LEDPattern {
    public:
        constexpr FadePattern(RgbColor left, RgbColor right, bool surrenderShowing);
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;
    private:
        RgbColor mLeft;
        RgbColor mRight;
        bool mSurrenderShowing;

        int32_t mColorCounter = 0;
    };

    constexpr FadePattern::FadePattern(RgbColor left, RgbColor right, bool surrenderShowing) 
        : mLeft(left)
        , mRight(right)
        , mSurrenderShowing(surrenderShowing)
    { }
}

#endif