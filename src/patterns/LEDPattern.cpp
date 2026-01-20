#include "patterns/LEDPattern.hpp"

namespace Loml {
    void LEDPattern::Interrupt() {
        Serial.println("Interrupted");
        mInterrupted = true;
    }

    void LEDPattern::Display(LEDStrip& led) {
        DisplayImpl(led);
        mInterrupted = false;
    }

    [[nodiscard]] auto LEDPattern::Delay(int64_t delayMs) -> bool {
        vTaskDelay(pdMS_TO_TICKS(delayMs));
        return !mInterrupted;
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
        led.Show();
    }
}