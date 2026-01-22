#include "patterns/Colors.hpp"
#include "patterns/FadePattern.hpp"

namespace Loml {
    void FadePattern::DisplayImpl(LEDStrip& led) {
        for (const auto& level : Levels) {
            for (auto pos : level) {
                led.SetPixelColor(pos, 
                    RgbColor::LinearBlend(
                        Colors::Blue, Colors::Purple, (mColorCounter % 14) / 14.f
                    ).Dim(5)
                );
            }
            mColorCounter++;
        }
        mColorCounter++;
        
        if (!mSurrenderShowing) {
            led.Show();
            Delay(20);
        }
    }
}
