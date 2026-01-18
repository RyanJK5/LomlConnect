#ifndef __LEDPattern_hpp__
#define __LEDPattern_hpp__

#include <NeoPixelBus.h>

namespace Loml {
    using LEDStrip = NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>;

    class LEDPattern {
    public:
        LEDPattern(uint64_t tickDelayMs);

        void Update(LEDStrip& led);
    protected:
        virtual void Display(LEDStrip& led) = 0;
    protected:
        static void DimAll(LEDStrip& led);
        static void BrightenAll(LEDStrip& led);
    private:
        uint64_t mTickDelayMs;
        uint64_t mLastTimeMs = 0;
    };
}

#endif