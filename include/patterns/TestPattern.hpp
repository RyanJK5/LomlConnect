#ifndef __TestPattern_hpp__
#define __TestPattern_hpp__

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class TestPattern : public LEDPattern {
    public:
        TestPattern();
    protected:
        virtual void Display(LEDStrip& led) override final;
    private:
        int32_t mColorIndex = 0;
    };
}

#endif