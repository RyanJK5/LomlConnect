#ifndef __LomlPattern_hpp__
#define __LomlPattern_hpp__

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class LomlPattern : public LEDPattern {
    public:
        LomlPattern() = default;
        
        virtual void DisplayImpl(LEDStrip& led) override final;        
    };
}

#endif