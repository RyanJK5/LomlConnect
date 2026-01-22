#ifndef FadePattern_h_
#define FadePattern_h_

#include "patterns/BackgroundPattern.hpp"

namespace Loml {
    template <int LevelCount>
    class FadePattern : public BackgroundPattern {
    public:
        using Array = std::array<std::vector<int32_t>, LevelCount>;

        constexpr FadePattern(bool inBackground, const Array& levels, RgbColor left, RgbColor right);
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;
    private:
        Array mLevels;

        RgbColor mLeft;
        RgbColor mRight;

        int32_t mColorCounter = 0;
    };

    template <int LevelCount>
    constexpr FadePattern<LevelCount>::FadePattern(bool inBackground, const Array& levels, RgbColor left, RgbColor right) 
        : BackgroundPattern(inBackground)
        , mLevels(levels)
        , mLeft(left)
        , mRight(right)
    { }

    template <int LevelCount>
    void FadePattern<LevelCount>::DisplayImpl(LEDStrip& led) {
        for (const auto& level : mLevels) {
            for (auto pos : level) {
                led.SetPixelColor(pos, 
                    RgbColor::LinearBlend(
                        mLeft, mRight, (mColorCounter % mLevels.size()) / static_cast<float>(mLevels.size())
                    ).Dim(5)
                );
            }
            mColorCounter++;
        }
        mColorCounter++;
        
        if (!InBackground()) {
            led.Show();
            std::ignore = Delay(20);
        }
    }
}

#endif