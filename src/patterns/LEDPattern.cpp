#include "patterns/LEDPattern.hpp"

namespace Loml {
    void LEDPattern::Interrupt() {
        Serial.println("Interrupted");
        mLifetimeMs = -1;
        mInterrupted = true;
    }

    void LEDPattern::SetLifetime(int64_t lifetimeMs) {
        assert(lifetimeMs >= 0);
        mLifetimeMs = lifetimeMs;
    }

    auto LEDPattern::Display(LEDStrip& led) -> bool {
        DisplayImpl(led);
        mInterrupted = false;
        if (mLifetimeMs >= 0) {
            return mLifetimeMs > 0;
        }
        else {
            return true;
        }
    }

    [[nodiscard]] auto LEDPattern::Delay(int64_t delayMs) -> bool {
        vTaskDelay(pdMS_TO_TICKS(delayMs));
        if (mLifetimeMs >= 0) {
            mLifetimeMs = std::max(0LL, mLifetimeMs - delayMs);
        }
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