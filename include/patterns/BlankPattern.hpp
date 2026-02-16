#ifndef BlankPattern_hpp_
#define BlankPattern_hpp_

#include "patterns/LEDPattern.hpp"

namespace Loml {
    // Pattern that displays nothing. Essentially "turning off" the display.
    class BlankPattern : public LEDPattern {
    public: 
        constexpr BlankPattern() = default;
    protected:
        void DisplayImpl(LEDStrip& led) override final {
            led.Show();
            [[maybe_unused]] auto success = Delay(5);
        }
    };
}

#endif