#ifndef LEDPattern_hpp_
#define LEDPattern_hpp_

#include <atomic>
#include <NeoPixelBus.h>

#include "patterns/PatternSymbols.hpp"

namespace Loml {
    using LEDStrip = NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod>;

    // Implementation of the strategy design pattern for displaying a pattern on the LED board.
    class LEDPattern {
    public:
        constexpr LEDPattern() = default;
        virtual ~LEDPattern() = default;
        
        // Interrupt the pattern's display animation in a thread-safe way.
        void Interrupt();
        // Set the pattern to expire after lifetimeMs ticks. It is the user's responsibility to
        // handle an expired pattern by checking the return value of Display().
        void SetLifetime(int64_t lifetimeMs);

        // Returns false if the pattern has expired.
        [[nodiscard]] auto Display(LEDStrip& led) -> bool;
    protected:
        virtual void DisplayImpl(LEDStrip& led) = 0;
    
        [[nodiscard]] auto Delay(int64_t delayMs) -> bool;

        static void DimRange(LEDStrip& led, uint16_t start = 0, uint16_t length = 0);
        static void BrightenRange(LEDStrip& led, uint16_t start = 0, uint16_t length = 0);
    private:
        std::atomic<bool> mInterrupted = false;
        int64_t mLifetimeMs = -1;
    };
}

#endif