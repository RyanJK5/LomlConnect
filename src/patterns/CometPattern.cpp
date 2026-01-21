#include "patterns/Colors.hpp"
#include "patterns/CometPattern.hpp"

namespace Loml {
    void CometPattern::DisplayImpl(LEDStrip& led) {
        constexpr static auto maxLength = *std::max_element(RingLengths.begin(), RingLengths.end());
        
        auto colorIndex = 0;
        for (auto i = 0; i < maxLength; i++) {
            for (auto k = 0; k <= i; k++) {
                for (auto j = 0; j < RingLengths.size(); j++) {
                    const auto offset = static_cast<float>(RingLengths[j]) / maxLength * k;
                    led.SetPixelColor(RingStartPositions[j] + offset, mRingColors.at((j + colorIndex) % mRingColors.size()).Dim(20));
                }
            }
            led.Show();
            if (!Delay(50)) {
                return;
            }
            colorIndex++;
        }

        for (auto i = 0; i < maxLength; i++) {
            for (auto k = i; k < maxLength; k++) {
                for (auto j = 0; j < RingLengths.size(); j++) {
                    const auto offset = static_cast<float>(RingLengths[j]) / maxLength * k;
                    led.SetPixelColor(RingStartPositions[j] + offset, 
                        k == i ? Colors::Black : mRingColors.at((j + colorIndex) % mRingColors.size()).Dim(20));
                }
            }
            led.Show();
            if (!Delay(50)) {
                return;
            }
            colorIndex++;
        }
    }
}