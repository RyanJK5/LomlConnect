#ifndef WiFiController_hpp_
#define WiFiController_hpp_

#include <PubSubClient.h>
#include <WiFiClientSecure.h>

#include "controllers/Controller.hpp"
#include "controllers/LEDResult.hpp"
#include "controllers/ControllerSubscriber.hpp"

namespace Loml {
    class WiFiController;

    struct LocalSettings {
        const char* NetworkName     = nullptr;
        const char* Username        = nullptr;
        const char* Password        = nullptr;
    
        [[nodiscard]] auto IsEnterprise() const -> bool { return Username != nullptr; }
    };

    struct ServerSettings {
        int32_t     Port           = 0;
        const char* NetworkName    = nullptr;
        const char* SessionID      = nullptr;
        const char* Subscription   = nullptr;
        const char* Username       = nullptr;
        const char* Password       = nullptr;
    };

    template <>
    struct ControllerSettings<WiFiController> {
        LocalSettings Local = {};
        ServerSettings Server = {};
    };

    template <>
    struct ControllerResult<WiFiController> {
        size_t PatternIndex = 0;
    };

    using WiFiSettings = ControllerSettings<WiFiController>;
    using WiFiResult   = ControllerResult<WiFiController>;

    class WiFiController 
        : public Controller<WiFiController>
        , public ControllerSubscriber<LEDController> {
    public:
        friend Controller<WiFiController>;
        
        WiFiController(const WiFiSettings& settings);

        void OnMessage(const LEDResult& result) override final;
    private:
        void Reconnect();

        void UpdateImpl();
    private:
        ServerSettings   mServerSettings;
        WiFiClientSecure mWifiClient;
        PubSubClient     mPubSub;
    };
}

#endif