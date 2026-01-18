#include <memory>
#include <variant>

#include "controllers/LEDController.hpp"
#include "patterns/TestPattern.hpp"
#include "patterns/CometPattern.hpp"

namespace Loml {
    LEDController::LEDController(const LEDSettings& settings) 
        : Controller{settings}
        , mStrip{settings.LightCount, settings.PinNumber} {
        mPatterns.emplace_back(std::make_unique<TestPattern>());
        mPatterns.emplace_back(std::make_unique<CometPattern>());
        mStrip.Begin();
    }
    
    void LEDController::OnMessage(const ButtonResult& args) {
        if (args.Event == ButtonEvent::Short) {
            mCurrentIndex = (mCurrentIndex + 1) % mPatterns.size();
        }
    }
    
    void LEDController::OnMessage(const WiFiResult& args) { }
    
    void LEDController::UpdateImpl() {
        vTaskDelay(pdMS_TO_TICKS(16));
        mPatterns.at(mCurrentIndex)->Update(mStrip);
    }
}
