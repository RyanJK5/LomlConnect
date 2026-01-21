#include "patterns/CrazyPattern.hpp"
#include "patterns/Colors.hpp"

namespace Loml {
    void CrazyPattern::DisplayImpl(LEDStrip& led) {
        constexpr static auto colorWheel = [](uint8_t pos) {
            constexpr static auto max = 255;
            pos = max - pos;

            if (pos < 85) {
                return RgbColor{max - pos * 3, 0, pos * 3};
            } else if (pos < 170) {
                pos -= 85;
                return RgbColor{0, pos * 3, max - pos * 3};
            } else {
                pos -= 170;
                return RgbColor{pos * 3, max - pos * 3, 0};
            }
        };
        
        for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
            for (int q = 0; q < 3; q++) {
                for (int i = 0; i < led.PixelCount(); i += 3) {
                    led.SetPixelColor(i + q, colorWheel( (i + j) % 255).Dim(30)); //turn every third pixel on
                }
                led.Show();

                if (!Delay(1)) {
                    return;
                }

                for (int i = 0; i < led.PixelCount(); i = i + 3) {
                    led.SetPixelColor(i + q, RgbColor{0});      //turn every third pixel off
                }
                led.Show();
            }
        }
    }
}