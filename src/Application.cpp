#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "Application.hpp"

namespace Loml {
    Application::Application(const LEDSettings& ledSetup, const ButtonSettings& buttonSetup, const WiFiSettings& wifiSetup) 
        : mLED(ledSetup)
        , mButton(buttonSetup)
        , mWiFi(wifiSetup) {
        mLED.AddSubscriber(mWiFi);
        mButton.AddSubscriber(mLED);
        mWiFi.AddSubscriber(mLED);
    }
    
    void Application::Begin() {
        mButton.CreateTask(TaskSettings{.Name = "ButtonTask", .StackDepth = 4096,  .CoreID = 1});
        mButton.CreateTask(TaskSettings{.Name = "WiFiTask",   .StackDepth = 12228, .CoreID = 0});
        mButton.CreateTask(TaskSettings{.Name = "LEDTask",    .StackDepth = 4096,  .CoreID = 0});
    }
}
