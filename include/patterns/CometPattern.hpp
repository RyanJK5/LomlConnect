#ifndef __CometPattern_hpp__
#define __CometPattern_hpp__

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class CometPattern : public LEDPattern {
    public:
        CometPattern();
    protected:
        virtual void Display(LEDStrip& led) override final;        
    private:
        bool     mLightNewPixel  = true;
        uint16_t mStripPos = 0;
    };
}

#endif