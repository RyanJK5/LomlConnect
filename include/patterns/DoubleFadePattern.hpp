#ifndef DoubleFadePattern_hpp_
#define DoubleFadePattern_hpp_

#include "patterns/BackgroundPattern.hpp"
#include "patterns/FadePattern.hpp"

namespace Loml {
    template <int LevelCount>
    class DoubleFadePattern : public BackgroundPattern {
    public:
        constexpr DoubleFadePattern(
            bool isBackground, const typename FadePattern<LevelCount>::Array& arr,
            RgbColor left1, RgbColor right1, 
            RgbColor left2, RgbColor right2
        );
    protected:
        virtual void DisplayImpl(LEDStrip& led) override final;
    private:
        RgbColor mLeft1;
        RgbColor mLeft2;
        RgbColor mRight1;
        RgbColor mRight2;
        
        uint8_t mBlendAmount = 0;
        bool mIncreasing = true;
        
        FadePattern<LevelCount> mFade;
    };

    template <int LevelCount>
    constexpr DoubleFadePattern<LevelCount>::DoubleFadePattern(
        bool isBackground, const typename FadePattern<LevelCount>::Array& arr,
        RgbColor left1, RgbColor right1, 
        RgbColor left2, RgbColor right2
    ) 
        : BackgroundPattern(isBackground)
        , mLeft1(left1)
        , mLeft2(left2)
        , mRight1(right1)
        , mRight2(right2)
        , mFade(isBackground, arr, left1, right1)
    { }

    template <int LevelCount>
    void DoubleFadePattern<LevelCount>::DisplayImpl(LEDStrip& led) {
        mFade.SetColors(
            RgbColor::LinearBlend(mLeft1, mLeft2, mBlendAmount),
            RgbColor::LinearBlend(mRight1, mRight2, mBlendAmount)
        );

        constexpr static auto delta = static_cast<uint8_t>(5);
        mBlendAmount += mIncreasing ? delta : -delta;
        if (mBlendAmount == 0 || mBlendAmount == std::numeric_limits<uint8_t>::max()) {
            mIncreasing = !mIncreasing;
        }
        
        mFade.Display(led);
    }
}

#endif