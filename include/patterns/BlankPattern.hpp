#ifndef BlankPattern_hpp_
#define BlankPattern_hpp_

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class BlankPattern : public LEDPattern {
    public: 
        constexpr BlankPattern() = default;
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final {
            led.Show();
            std::ignore = Delay(5);
        }
    };
}

#endif