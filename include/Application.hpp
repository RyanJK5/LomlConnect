#ifndef Application_hpp_
#define Application_hpp_

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#include "controllers/LEDController.hpp"
#include "controllers/ButtonController.hpp"
#include "controllers/WiFiController.hpp"

namespace Loml {
    class Application {
    public:
        Application(const LEDSettings& ledSetup, const ButtonSettings& buttonSetup, const WiFiSettings& wifiSetup);
        
        void Begin();
    private:
        LEDController mLED;
        ButtonController mButton;
        WiFiController mWiFi;
    };
}

#endif