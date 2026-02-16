#ifndef BackgroundPattern_hpp_
#define BackgroundPattern_hpp_

#include "patterns/LEDPattern.hpp"

namespace Loml {
    // A pattern that can be overlayed behind another pattern, primarily for use with LetterPatterns.
    // BackgroundPatterns are expected to update more frequently than typical patterns. When constructed
    // with inBackground = true, they should not delay or display their pattern.
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