#ifndef CometPattern_hpp_
#define CometPattern_hpp_

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class CometPattern : public LEDPattern {
    public:
        constexpr CometPattern(const std::array<RgbColor, 6>& ringColors);
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;
    private:
        std::array<RgbColor, 6> mRingColors;
    };

    constexpr CometPattern::CometPattern(const std::array<RgbColor, 6>& ringColors) 
        : mRingColors(ringColors)
    { }
}

#endif