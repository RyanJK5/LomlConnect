#ifndef __Config_hpp__
#define __Config_hpp__

#include "controllers/LEDController.hpp"
#include "controllers/ButtonController.hpp"
#include "controllers/WiFiController.hpp"

namespace Loml::Config {
    constexpr inline LEDSettings DefaultLEDSettings {
        .LightCount = 93,
        .PinNumber  = 4
    };

    constexpr inline ButtonSettings DefaultButtonSettings {
        .PinNumber           = 18,
        .LongPressDurationMs = 3000
    };

    constexpr inline LocalSettings DefaultLocalSettings {
        .NetworkName = LOML_LOCAL_NETWORK_NAME,
        .Username    = LOML_LOCAL_USERNAME,
        .Password    = LOML_LOCAL_PASSWORD
    };

    constexpr inline ServerSettings DefaultServerSettings {
        .Port         = LOML_SERVER_PORT,
        .NetworkName  = LOML_SERVER_URL,
        .SessionID    = LOML_SERVER_SESSION_ID,
        .Subscription = LOML_SERVER_SUBSCRIPTION,
        .Username     = LOML_SERVER_USERNAME,
        .Password     = LOML_SERVER_PASSWORD
    };
}

#endif