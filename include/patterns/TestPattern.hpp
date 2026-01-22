#ifndef TestPattern_hpp_
#define TestPattern_hpp_

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class TestPattern : public LEDPattern {
    public:
        TestPattern() = default;
     
        virtual void DisplayImpl(LEDStrip& led) override final;
    };
}

#endif