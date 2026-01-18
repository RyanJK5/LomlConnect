#include "patterns/CometPattern.hpp"

namespace Loml {
    CometPattern::CometPattern()
        : LEDPattern(10)
    { }
    
    void CometPattern::Display(LEDStrip& led) {
        if (mLightNewPixel) {
            led.SetPixelColor(mStripPos, RgbColor(0, 0, 30));
            mStripPos = (mStripPos + 1) % led.PixelCount();
        }
        FadeAll(led);
        
        mLightNewPixel = !mLightNewPixel;
        led.Show();
    }
}