#ifndef HeartPattern_hpp_
#define HeartPattern_hpp_

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