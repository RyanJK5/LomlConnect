#ifndef __BackgroundLEDPattern_hpp__
#define __BackgroundLEDPattern_hpp__

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class BackgroundLEDPattern : public LEDPattern {
    public:
        constexpr BackgroundLEDPattern(bool inBackground);
        virtual ~BackgroundLEDPattern() = default;
    protected:
        [[nodiscard]] constexpr auto InBackground() const -> bool { return mInBackground; }
    private:
        bool mInBackground;
    };

    constexpr BackgroundLEDPattern::BackgroundLEDPattern(bool inBackground) 
        : mInBackground(inBackground)
    { }
}

#endif