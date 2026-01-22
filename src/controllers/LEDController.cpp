#include <memory>
#include <random>
#include <variant>

#include "controllers/LEDController.hpp"
#include "patterns/TestPattern.hpp"
#include "patterns/CrazyPattern.hpp"
#include "patterns/CometPattern.hpp"
#include "patterns/BeatPattern.hpp"
#include "patterns/FadePattern.hpp"
#include "patterns/BlankPattern.hpp"
#include "patterns/RadiatePattern.hpp"
#include "patterns/LomlPattern.hpp"

namespace Loml {
    LEDController::LEDController(const LEDSettings& settings) 
        : Controller{settings}
        , mStrip{settings.LightCount, settings.PinNumber} {

        LomlPattern<FadePattern> a {Colors::Blue, Colors::Purple};
        mPatterns.emplace_back(std::make_unique<BlankPattern>());
        mPatterns.emplace_back(std::make_unique<CrazyPattern>());
        mPatterns.emplace_back(std::make_unique<RadiatePattern<6>>(std::array{
            Colors::HotPink,
            Colors::Magenta,
            Colors::BlueViolet,
            Colors::RoyalBlue,
            Colors::Cyan,
            Colors::Teal
        }));
        mPatterns.emplace_back(std::make_unique<CometPattern>(std::array{
            Colors::HotPink,
            Colors::Magenta,
            Colors::BlueViolet,
            Colors::RoyalBlue,
            Colors::Cyan,
            Colors::Teal
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
        mReceiveIndex = mPatterns.size();

        mPatterns.emplace_back(std::make_unique<LomlPattern<FadePattern>>(
            Colors::Blue, 
            Colors::Purple
        ));

        mStrip.Begin();
    }
    
    void LEDController::OnMessage(const ButtonResult& args) {
        if (args.Event == ButtonEvent::Short) {
            mPatterns.at(mCurrentIndex)->Interrupt();
            mCurrentIndex = (mCurrentIndex + 1) % mReceiveIndex;
        }
    }
    
    void LEDController::OnMessage(const WiFiResult& args) {
        Serial.println("Changing pattern");

        static std::random_device rd{};
        static std::mt19937 gen{rd()};
        std::uniform_int_distribution<> dis{mReceiveIndex, mPatterns.size() - 1};
		
        mPatterns.at(mCurrentIndex)->Interrupt();
        mCurrentIndex = dis(gen);
    }
    
    void LEDController::UpdateImpl() {
        mStrip.ClearTo(Colors::Black);
        mPatterns.at(mCurrentIndex)->Display(mStrip);
    }
}
