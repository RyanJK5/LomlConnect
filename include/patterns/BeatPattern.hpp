#ifndef __BeatPattern_hpp__
#define __BeatPattern_hpp__

#include "patterns/LEDPattern.hpp"
#include "patterns/Colors.hpp"

#include <array>

namespace Loml {
    class BeatPattern : public LEDPattern {
    public:
        BeatPattern();
    protected:
        virtual void Display(LEDStrip& led) override final;        
    private:
        constexpr static std::array Colors{
            Colors::Fuchsia,
            Colors::Magenta,
            Colors::LightPurple,
            Colors::Lavender,
            Colors::Plum
        };
        uint16_t mStripIndex = 0;
    };
}

#endif