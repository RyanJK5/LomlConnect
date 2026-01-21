#ifndef __BlankPattern_hpp__
#define __BlankPattern_hpp__

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class BlankPattern : public LEDPattern {
    public: 
        constexpr BlankPattern() = default;
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final {
            vTaskDelay(5);
            led.Show();
        }
    };
}

#endif