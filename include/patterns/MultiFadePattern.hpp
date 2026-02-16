#ifndef MultiFadePattern_hpp_
#define MultiFadePattern_hpp_

#include "patterns/BackgroundPattern.hpp"
#include "patterns/FadePattern.hpp"

namespace Loml {
    // A background pattern that crossfades between two colors over various levels. It then also
    // crossfades the colors on each end between various colors. Basically, pass in a bunch of
    // colors and observe the effect 
    template <int LevelCount, int ColorCount>
    class MultiFadePattern : public BackgroundPattern {
    public:
        constexpr MultiFadePattern(
            bool isBackground, const typename FadePattern<LevelCount>::Array& arr,
            const std::array<RgbColor, ColorCount>& leftColors,
            const std::array<RgbColor, ColorCount>& rightColors
        );
    protected:
        void DisplayImpl(LEDStrip& led) override final;
    private:
        std::array<RgbColor, ColorCount> mLeftColors;
        std::array<RgbColor, ColorCount> mRightColors;
        
        uint8_t mBlendAmount = 0;
        
        FadePattern<LevelCount> mFade;
        size_t mFadeIndex = 0;
    };

    template <int LevelCount, int ColorCount>
    constexpr MultiFadePattern<LevelCount, ColorCount>::MultiFadePattern(
        bool isBackground, const typename FadePattern<LevelCount>::Array& arr,
        const std::array<RgbColor, ColorCount>& leftColors,
        const std::array<RgbColor, ColorCount>& rightColors
    ) 
        : BackgroundPattern(isBackground)
        , mLeftColors(leftColors)
        , mRightColors(rightColors)
        , mFade(isBackground, arr, leftColors[0], rightColors[0])
    { }

    template <int LevelCount, int ColorCount>
    void MultiFadePattern<LevelCount, ColorCount>::DisplayImpl(LEDStrip& led) {
        // MultiFade is just a wrapper around FadePattern. We simply vary the colors
        // that FadePattern uses every tick, and then call its display method.
        
        size_t nextIndex = (mFadeIndex + 1) % mLeftColors.size();
        mFade.SetColors(
            RgbColor::LinearBlend(mLeftColors[mFadeIndex], mLeftColors[nextIndex], mBlendAmount),
            RgbColor::LinearBlend(mRightColors[mFadeIndex], mRightColors[nextIndex], mBlendAmount)
        );

        constexpr static auto delta = static_cast<uint8_t>(5);
        if (mBlendAmount == std::numeric_limits<uint8_t>::max()) {
            mBlendAmount = 0;
            mFadeIndex = nextIndex;
        }
        mBlendAmount += delta;
        [[maybe_unused]] const auto expired = mFade.Display(led); // We know that mFade has no lifetime
    }
}

#endif