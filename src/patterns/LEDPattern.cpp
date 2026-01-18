#include "patterns/LEDPattern.hpp"

namespace Loml {
    LEDPattern::LEDPattern(uint64_t tickDelayMs)
        : mTickDelayMs(tickDelayMs)
    { }
    
    void LEDPattern::Update(LEDStrip& led) {
        if (millis() - mLastTimeMs < mTickDelayMs) {
            return;
        }
        mLastTimeMs = millis();
        Display(led);
    }
    
    void LEDPattern::FadeAll(LEDStrip& led) {
        for (uint16_t i = 0; i < led.PixelCount(); i++) {
            auto color = led.GetPixelColor(i);
            color.Dim(255 - 1);
            led.SetPixelColor(i, color);
        }
        led.Show();
    }
}