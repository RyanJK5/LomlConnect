#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "Application.hpp"

namespace Loml {
    Application::Application(const LEDSettings& ledSetup, const ButtonSettings& buttonSetup, const WiFiSettings& wifiSetup) 
        : mLED(ledSetup)
        , mButton(buttonSetup)
        , mWiFi(wifiSetup) {
        mButton.AddSubscriber(mWiFi);
        mButton.AddSubscriber(mLED);
    }
    
    void Application::Begin() {
        mButton.CreateTask(TaskSettings{"ButtonTask", 4096, 1});
        mWiFi.CreateTask(TaskSettings{"WiFiTask", 12228, 0});
        mLED.CreateTask(TaskSettings{"LEDTask", 4096, 0});
    }
}
