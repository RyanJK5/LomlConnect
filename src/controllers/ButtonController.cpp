#include <Arduino.h>

#include "controllers/ButtonController.hpp"

Loml::ButtonController::ButtonController(const ButtonSettings& settings) 
    : Controller{settings}
    , mSettings{settings}
{
	pinMode(settings.PinNumber, INPUT_PULLUP);
}

void Loml::ButtonController::UpdateImpl() {
    vTaskDelay(pdMS_TO_TICKS(50));

    if (digitalRead(mSettings.PinNumber) != LOW) {
        return;
    }

    auto start = millis();
    while (digitalRead(mSettings.PinNumber) == LOW);
    auto end = millis();

    if (end - start < mSettings.LongPressDurationMs) {
        Publish(ButtonResult{.Event = ButtonEvent::Short});
    }
    else {
        Publish(ButtonResult{.Event = ButtonEvent::Long});
    }
}