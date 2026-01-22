#ifndef __HeartPattern_hpp__
#define __HeartPattern_hpp__

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class HeartPattern : public LEDPattern {
    public:
        HeartPattern() = default;
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;        
    };
}

#endif