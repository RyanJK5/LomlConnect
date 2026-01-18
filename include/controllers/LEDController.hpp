#ifndef __LEDController_hpp__
#define __LEDController_hpp__

#include <NeoPixelBus.h>
#include <cstdint>
#include <memory>

#include "controllers/Controller.hpp"
#include "controllers/ButtonController.hpp"
#include "controllers/WiFiController.hpp"
#include "patterns/LEDPattern.hpp"

namespace Loml {
    class LEDController;

    template <>
    struct ControllerSettings<LEDController> {
        uint16_t LightCount = 0;
        uint8_t  PinNumber  = 0;
    };

    using LEDSettings = ControllerSettings<LEDController>;
    using LEDResult = ControllerResult<LEDController>;

    class LEDController 
        : public Controller<LEDController>
        , public ControllerSubscriber<ButtonController>
        , public ControllerSubscriber<WiFiController> {
    public:
        friend Controller<LEDController>;
        
        LEDController(const LEDSettings& settings);

        virtual void OnMessage(const ButtonResult& args) override final;
        virtual void OnMessage(const WiFiResult& args) override final;
    private:
        void UpdateImpl();
    private:
        NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> mStrip;
        
        std::vector<std::unique_ptr<LEDPattern>> mPatterns;
        size_t mCurrentIndex = 0;
    };
}

#endif