#ifndef __WiFiController_hpp__
#define __WiFiController_hpp__

#include <PubSubClient.h>
#include <WiFiClientSecure.h>

#include "controllers/Controller.hpp"
#include "controllers/ButtonController.hpp"
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
        const char* Topic          = nullptr;
        const char* Username       = nullptr;
        const char* Password       = nullptr;
    };

    template <>
    struct ControllerSettings<WiFiController> {
        LocalSettings Local = {};
        ServerSettings Server = {};
    };

    using WiFiSettings = ControllerSettings<WiFiController>;
    using WiFiResult   = ControllerResult<WiFiController>;

    class WiFiController 
        : public Controller<WiFiController>
        , public ControllerSubscriber<ButtonController> {
    public:
        friend Controller<WiFiController>;
        
        WiFiController(const WiFiSettings& settings);

        void Publish();

        virtual void OnMessage(const ButtonResult& result) override final;
    private:
        void Reconnect();

        void UpdateImpl();
    private:
        QueueHandle_t    mOutQueue;
        
        ServerSettings   mServerSettings;
        WiFiClientSecure mWifiClient;
        PubSubClient     mPubSub;
    };
}

#endif