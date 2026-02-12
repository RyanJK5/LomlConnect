#include <memory>
#include <random>
#include <variant>

#include "controllers/LEDController.hpp"
#include "patterns/CrazyPattern.hpp"
#include "patterns/CometPattern.hpp"
#include "patterns/BeatPattern.hpp"
#include "patterns/FadePattern.hpp"
#include "patterns/HeartPattern.hpp"
#include "patterns/MultiFadePattern.hpp"
#include "patterns/BlankPattern.hpp"
#include "patterns/RadiatePattern.hpp"
#include "patterns/LomlPattern.hpp"
#include "patterns/XOPattern.hpp"

namespace Loml {
    LEDController::LEDController(const LEDSettings& settings) 
        : Controller(settings)
        , mStrip(settings.LightCount, settings.PinNumber) {

        AddNormalPatterns();
        mReceiveIndex = mPatterns.size();
        AddSpecialPatterns();

        mStrip.Begin();
    }
    
    void LEDController::AddNormalPatterns() {
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

        mPatterns.emplace_back(std::make_unique<MultiFadePattern<Levels.size(), 4>>(
            false,
            Levels,
            std::array {
                Colors::Blue,
                Colors::Purple,
                Colors::Green,
                Colors::FireBrick
            },
            std::array {
                Colors::Red,
                Colors::Aqua,
                Colors::Yellow,
                Colors::ElectricPurple
            }
        ));
    }

    void LEDController::AddSpecialPatterns() {
        constexpr static auto levelSize = Levels.size();
        
        mPatterns.emplace_back(std::make_unique<HeartPattern<FadePattern<RingLevels.size()>>>(
            Colors::Red,
            RingLevels,
            Colors::Blue,
            Colors::Purple
        ));
        mPatterns.emplace_back(std::make_unique<LomlPattern<FadePattern<levelSize>>>(
            Colors::Red,
            Levels,
            Colors::Blue, 
            Colors::Purple
        ));
        mPatterns.emplace_back(std::make_unique<XOPattern<FadePattern<levelSize>>>(
            Colors::Red,
            Levels,
            Colors::Blue, 
            Colors::Purple
        ));
        mPatterns.emplace_back(std::make_unique<LomlPattern<MultiFadePattern<levelSize, 2>>>(
            Colors::Red,
            Levels,
            std::array {
                Colors::Red,
                Colors::LightYellow,
            },
            std::array {
                Colors::Pink,
                Colors::Orange
            }
        ));
        mPatterns.emplace_back(std::make_unique<XOPattern<MultiFadePattern<levelSize, 2>>>(
            Colors::Red,
            Levels,
            std::array {
                Colors::Red,
                Colors::LightYellow,
            },
            std::array {
                Colors::Pink,
                Colors::Orange
            }
        ));
    }

    void LEDController::OnMessage(const ButtonResult& args) {
        if (args.Event == ButtonEvent::Short) {
            ChangePattern();
        }
    }
    
    void LEDController::OnMessage(const WiFiResult& args) {
        Serial.println("Changing pattern");

        static std::random_device rd{};
        static std::mt19937 gen{rd()};
        std::uniform_int_distribution<> dis{mReceiveIndex, static_cast<int32_t>(mPatterns.size()) - 1};
		
        auto newIndex = dis(gen);
        while (newIndex == mCurrentIndex) {
            newIndex = dis(gen);
        }

        mPatterns.at(mCurrentIndex)->Interrupt();
        mCurrentIndex = newIndex;
        mPatterns.at(newIndex)->SetLifetime(5000);
    }
    
    void LEDController::ChangePattern() {
        mPatterns.at(mCurrentIndex)->Interrupt();
        if (mCurrentIndex >= mReceiveIndex) {
            mCurrentIndex = mPrevIndex;
        }
        else {
            mCurrentIndex = (mCurrentIndex + 1) % mReceiveIndex;
        }
        mPrevIndex = mCurrentIndex;
    }

    void LEDController::UpdateImpl() {
        mStrip.ClearTo(Colors::Black);
        
        auto success = mPatterns.at(mCurrentIndex)->Display(mStrip);
        if (!success) {
            ChangePattern();
        }
    }
}
