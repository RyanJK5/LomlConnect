#include <Arduino.h>

#include "controllers/ButtonController.hpp"

Loml::ButtonController::ButtonController(const ButtonSettings& settings) 
    : Controller(settings)
    , mSettings(settings)
{
	pinMode(settings.PinNumber, INPUT_PULLUP);
}

void Loml::ButtonController::UpdateImpl() {
    vTaskDelay(pdMS_TO_TICKS(50)); // Refresh every 50ms

    if (digitalRead(mSettings.PinNumber) != LOW) { // LOW means button is down
        return;
    }

    const auto start = millis();
    while (digitalRead(mSettings.PinNumber) == LOW);
    const auto timeElapsed = millis() - start;

    if (timeElapsed < mSettings.LongPressDurationMs) {
        Publish(ButtonResult{.Event = ButtonEvent::Cycle});
    }
    else if (mMode == PatternMode::Sending) {
        mMode = PatternMode::Default;
        Publish(ButtonResult{.Event = ButtonEvent::SendMessage});
    }
    else {
        mMode = PatternMode::Sending;
        Publish(ButtonResult{.Event = ButtonEvent::SelectMessage});
    }
}