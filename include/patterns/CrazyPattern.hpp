#ifndef CrazyPattern_hpp_
#define CrazyPattern_hpp_

#include "patterns/LEDPattern.hpp"

namespace Loml {
    // Displays a gradient of colors that changes rapidly across the whole color wheel.
    // Credit to https://wiki.dfrobot.com/93_LEDs_WS2812B_RGB_6_Ring_Lamp_SKU_FIT0676 for implementation.
    class CrazyPattern : public LEDPattern {
    public:
        constexpr CrazyPattern() = default;
    protected:
        void DisplayImpl(LEDStrip& led) override final;
    };
}

#endif