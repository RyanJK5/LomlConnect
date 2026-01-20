#ifndef __CrazyPattern_hpp__
#define __CrazyPattern_hpp__

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class CrazyPattern : public LEDPattern {
    public:
        constexpr CrazyPattern() = default;
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;
    };
}

#endif