#ifndef BackgroundPattern_hpp_
#define BackgroundPattern_hpp_

#include "patterns/LEDPattern.hpp"

namespace Loml {
    class BackgroundPattern : public LEDPattern {
    public:
        constexpr BackgroundPattern(bool inBackground);
        virtual ~BackgroundPattern() = default;
    protected:
        [[nodiscard]] constexpr auto InBackground() const -> bool { return mInBackground; }
    private:
        bool mInBackground;
    };

    constexpr BackgroundPattern::BackgroundPattern(bool inBackground) 
        : mInBackground(inBackground)
    { }
}

#endif