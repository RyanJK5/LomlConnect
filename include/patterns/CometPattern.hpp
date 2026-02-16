#ifndef CometPattern_hpp_
#define CometPattern_hpp_

#include "patterns/LEDPattern.hpp"

namespace Loml {
    // Displays a wall of color that moves around the ring and fills it as it goes. It will then remove
    // the colors it placed down in the same sweeping motion.
    class CometPattern : public LEDPattern {
    public:
        constexpr CometPattern(const std::array<RgbColor, 6>& ringColors);
    protected:
        void DisplayImpl(LEDStrip& led) override final;
    private:
        std::array<RgbColor, 6> mRingColors;
    };

    constexpr CometPattern::CometPattern(const std::array<RgbColor, 6>& ringColors) 
        : mRingColors(ringColors)
    { }
}

#endif