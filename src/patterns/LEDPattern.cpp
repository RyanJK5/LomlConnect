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
    
    void LEDPattern::DimAll(LEDStrip& led) {
        for (uint16_t i = 0; i < led.PixelCount(); i++) {
            auto color = led.GetPixelColor(i);
            led.SetPixelColor(i, color.Dim(255 - 1));
        }
        led.Show();
    }

    void LEDPattern::BrightenAll(LEDStrip& led) {
        for (uint16_t i = 0; i < led.PixelCount(); i++) {
            auto color = led.GetPixelColor(i);
            led.SetPixelColor(i, color.Brighten(255 - 1));
        }
    }
}