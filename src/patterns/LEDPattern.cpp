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
    
    void LEDPattern::DimRange(LEDStrip& led, uint16_t start, uint16_t length) {
        if (length == 0) {
            length = led.PixelCount();
        }
        for (uint16_t i = start; i < start + length; i++) {
            const auto color = led.GetPixelColor(i);
            led.SetPixelColor(i, color.Dim(255 - 1));
        }
        led.Show();
    }

    void LEDPattern::BrightenRange(LEDStrip& led, uint16_t start, uint16_t length) {
        if (length == 0) {
            length = led.PixelCount();
        }
        for (uint16_t i = start; i < start + length; i++) {
            const auto color = led.GetPixelColor(i);
            led.SetPixelColor(i, color.Brighten(255 - 1));
        }
        led.Show();
    }
}