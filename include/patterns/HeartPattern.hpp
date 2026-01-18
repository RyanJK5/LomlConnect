#ifndef __HeartPattern_hpp__
#define __HeartPattern_hpp__

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class HeartPattern : public LEDPattern {
    public:
        HeartPattern();
    protected:
        virtual void Display(LEDStrip& led) override final;        
    private:
        uint16_t mStripPos = 0;
    };
}

#endif