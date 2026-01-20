#ifndef __TestPattern_hpp__
#define __TestPattern_hpp__

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class TestPattern : public LEDPattern {
    public:
        TestPattern() = default;
     
        virtual void DisplayImpl(LEDStrip& led) override final;
    };
}

#endif