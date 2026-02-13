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
    constexpr static auto ConfirmHoldTime = 50LL;

    LEDController::LEDController(const LEDSettings& settings) 
        : Controller(settings)
        , mStrip(settings.LightCount, settings.PinNumber) {

        AddNormalPatterns();
        AddSpecialPatterns();

        mConfirmPattern = std::make_unique<BeatPattern<1>>(std::array{Colors::LightBlue}, 10, ConfirmHoldTime);
        mConfirmPattern->SetLifetime(ConfirmHoldTime);

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
                Colors::SeaGreen,
                Colors::FireBrick
            },
            std::array {
                Colors::Red,
                Colors::Aqua,
                Colors::Teal,
                Colors::ElectricPurple
            }
        ));
    }

    void LEDController::AddSpecialPatterns() {
        constexpr static auto levelSize = Levels.size();
        
        mMessagePatterns.emplace_back(std::make_unique<BlankPattern>());
        mMessagePatterns.emplace_back(std::make_unique<HeartPattern<FadePattern<levelSize>>>(
            Colors::Red,
            Levels,
            Colors::Blue,
            Colors::Purple
        ));
        mMessagePatterns.emplace_back(std::make_unique<LomlPattern<FadePattern<levelSize>>>(
            Colors::Red,
            Levels,
            Colors::Blue, 
            Colors::Purple
        ));
        mMessagePatterns.emplace_back(std::make_unique<XOPattern<FadePattern<levelSize>>>(
            Colors::Red,
            Levels,
            Colors::Blue, 
            Colors::Purple
        ));
        mMessagePatterns.emplace_back(std::make_unique<HeartPattern<MultiFadePattern<levelSize, 2>>>(
            Colors::Aqua,
            Levels,
            std::array {
                Colors::Red,
                Colors::Red,
            },
            std::array {
                Colors::Pink,
                Colors::Purple
            }
        ));
        mMessagePatterns.emplace_back(std::make_unique<LomlPattern<MultiFadePattern<levelSize, 2>>>(
            Colors::Aqua,
            Levels,
            std::array {
                Colors::Red,
                Colors::Red,
            },
            std::array {
                Colors::Pink,
                Colors::Purple
            }
        ));
        mMessagePatterns.emplace_back(std::make_unique<XOPattern<MultiFadePattern<levelSize, 2>>>(
            Colors::Aqua,
            Levels,
            std::array {
                Colors::Red,
                Colors::Red,
            },
            std::array {
                Colors::Pink,
                Colors::Purple
            }
        ));
    }

    void LEDController::OnMessage(const ButtonResult& args) {
        switch (args.Event) {
            case ButtonEvent::Cycle:
                ChangePattern();
                break;
            case ButtonEvent::SelectMessage:
                mMode = PatternMode::Sending;
                mPatterns.at(mCurrentIndex)->Interrupt();
                mPrevIndex = mCurrentIndex;
                mCurrentIndex = 1;
                break;
            case ButtonEvent::SendMessage:
                mConfirmPattern->SetLifetime(ConfirmHoldTime);

                mMessagePatterns.at(mCurrentIndex)->Interrupt();
            
                if (mCurrentIndex != 0) {
                    mMode = PatternMode::ConfirmingSent;
                    Publish(LEDResult{.PatternIndex=static_cast<size_t>(mCurrentIndex)});
                }
                else {
                    mMode = PatternMode::Default;
                }
                mCurrentIndex = mPrevIndex;
                break;
        }
    }
    
    void LEDController::OnMessage(const WiFiResult& args) {
        Serial.println("Changing pattern");
        
        switch (mMode) {
            case PatternMode::Default:
                mPatterns.at(mCurrentIndex)->Interrupt();
                break;
            case PatternMode::ConfirmingSent:
            case PatternMode::ConfirmingReceived:
                mConfirmPattern->Interrupt();
                break;
            case PatternMode::Receiving:
            case PatternMode::Sending:
                mMessagePatterns.at(mCurrentIndex)->Interrupt();
                break;
        }
        mConfirmPattern->SetLifetime(ConfirmHoldTime);
		mMode = PatternMode::ConfirmingReceived;
        
        mPatterns.at(mCurrentIndex)->Interrupt();
        mCurrentIndex = args.PatternIndex;
    }
    
    void LEDController::ChangePattern() {
        switch (mMode) {
            case PatternMode::Default:
                mPatterns.at(mCurrentIndex)->Interrupt();
                mCurrentIndex = (mCurrentIndex + 1) % mPatterns.size();
                break;
            case PatternMode::Receiving:
                mMode = PatternMode::Default;
                mMessagePatterns.at(mCurrentIndex)->Interrupt();
                mCurrentIndex = mPrevIndex;
                break;
            case PatternMode::Sending:
                mMessagePatterns.at(mCurrentIndex)->Interrupt();
                mCurrentIndex = (mCurrentIndex + 1) % mMessagePatterns.size();
                break;
            case PatternMode::ConfirmingSent:
                mConfirmPattern->Interrupt();
                mCurrentIndex = mPrevIndex;
                break;
            case PatternMode::ConfirmingReceived:
                mConfirmPattern->Interrupt();
                break;
        }
    }

    void LEDController::UpdateImpl() {
        mStrip.ClearTo(Colors::Black);
        
        const bool success = [&]() {
            switch (mMode) {
                case PatternMode::Default:
                    return mPatterns.at(mCurrentIndex)->Display(mStrip);
                case PatternMode::ConfirmingSent:
                case PatternMode::ConfirmingReceived:
                    return mConfirmPattern->Display(mStrip);
                case PatternMode::Receiving:
                case PatternMode::Sending:
                    return mMessagePatterns.at(mCurrentIndex)->Display(mStrip);
            }
            return false;
        }();
        
        if (success) {
            return;
        }
        
        ChangePattern();
        switch (mMode) {
            case PatternMode::ConfirmingSent:
                mMode = PatternMode::Default;
                break;
            case PatternMode::ConfirmingReceived:
                mMode = PatternMode::Receiving;
                break;
            default:
                break;
        }
    }
}
