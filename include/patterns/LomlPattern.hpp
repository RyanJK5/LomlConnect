#ifndef __LomlPattern_hpp__
#define __LomlPattern_hpp__

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class LomlPattern : public LEDPattern {
    public:
        LomlPattern();
    protected:
        virtual void Display(LEDStrip& led) override final;        
    private:
        uint16_t mStripPos = 0;
    };
}

#endif