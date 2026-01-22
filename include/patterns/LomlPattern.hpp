#ifndef __LomlPattern_hpp__
#define __LomlPattern_hpp__

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class LomlPattern : public LEDPattern {
    public:
        constexpr LomlPattern() = default;
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;        
    };
}

#endif