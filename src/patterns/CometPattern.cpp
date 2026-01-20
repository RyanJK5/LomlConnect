#include "patterns/Colors.hpp"
#include "patterns/CometPattern.hpp"

namespace Loml {
    void CometPattern::DisplayImpl(LEDStrip& led) {
        constexpr static auto maxLength = *std::max_element(RingLengths.begin(), RingLengths.end());
        
        for (auto i = 0; i < maxLength; i++) {
            for (auto j = 0; j < RingLengths.size(); j++) {
                led.SetPixelColor(RingStartPositions[j] + (i % RingLengths[j]), mRingColors.at(j).Dim(20));
            }
            DimAll(led);
            if (!Delay(50)) {
                return;
            }
            DimAll(led);
            if (!Delay(50)) {
                return;
            }
        }
    }
}