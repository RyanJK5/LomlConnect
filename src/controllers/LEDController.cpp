#include <memory>
#include <variant>

#include "controllers/LEDController.hpp"
#include "patterns/TestPattern.hpp"
#include "patterns/CrazyPattern.hpp"
#include "patterns/CometPattern.hpp"
#include "patterns/BeatPattern.hpp"
#include "patterns/BlankPattern.hpp"

namespace Loml {
    LEDController::LEDController(const LEDSettings& settings) 
        : Controller{settings}
        , mStrip{settings.LightCount, settings.PinNumber} {
        mPatterns.emplace_back(std::make_unique<CrazyPattern>());
        mPatterns.emplace_back(std::make_unique<CometPattern>(std::array{
            Colors::HotPink,
            Colors::Magenta,
            Colors::BlueViolet,
            Colors::RoyalBlue,
            Colors::Cyan,
            Colors::Teal,
        }));
        mPatterns.emplace_back(std::make_unique<BeatPattern<7>>(std::array{
            Colors::HotPink,
            Colors::Magenta,
            Colors::BlueViolet,
            Colors::RoyalBlue,
            Colors::Cyan,
            Colors::Teal,
            Colors::SeaGreen
        }));
        mPatterns.emplace_back(std::make_unique<BlankPattern>());
        mStrip.Begin();
    }
    
    void LEDController::OnMessage(const ButtonResult& args) {
        if (args.Event == ButtonEvent::Short) {
            mPatterns.at(mCurrentIndex)->Interrupt();
            mCurrentIndex = (mCurrentIndex + 1) % mPatterns.size();
        }
    }
    
    void LEDController::OnMessage(const WiFiResult& args) { }
    
    void LEDController::UpdateImpl() {
        mStrip.ClearTo(Colors::Black);
        mPatterns.at(mCurrentIndex)->Display(mStrip);
    }
}
