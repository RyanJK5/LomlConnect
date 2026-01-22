#ifndef CrazyPattern_hpp_
#define CrazyPattern_hpp_

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