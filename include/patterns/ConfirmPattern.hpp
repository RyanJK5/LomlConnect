#ifndef ConfirmPattern_hpp_
#define ConfirmPattern_hpp_

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class ConfirmPattern : public LEDPattern {
    public:
        constexpr ConfirmPattern(RgbColor color);
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;
    private:
        RgbColor mColor;
    };

    ConfirmPattern::ConfirmPattern(RgbColor color)
        : mColor(color)
    { }
}

#endif