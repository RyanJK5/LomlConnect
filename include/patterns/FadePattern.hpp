#ifndef FadePattern_h_
#define FadePattern_h_

#include "patterns/BackgroundPattern.hpp"

#include <utility>

namespace Loml {
    // Fades between two provided colors across the various levels provided in the constructor.
    template <int LevelCount> // Number of levels
    class FadePattern : public BackgroundPattern {
    public:
        using Array = std::array<std::vector<int32_t>, LevelCount>; // To avoid verbosity

        constexpr FadePattern(bool inBackground, const Array& levels, RgbColor left, RgbColor right);
    
        constexpr void SetColors(RgbColor left, RgbColor right);
        [[nodiscard]] constexpr auto GetColors() const -> std::pair<RgbColor, RgbColor>;
    protected:
        void DisplayImpl(LEDStrip& led) override final;
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
            for (const auto pos : level) {
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
            [[maybe_unused]] auto success = Delay(20);
        }
    }

    template <int LevelCount>
    constexpr void FadePattern<LevelCount>::SetColors(RgbColor left, RgbColor right) {
        mLeft = left;
        mRight = right;
    }

    template <int LevelCount>
    constexpr auto FadePattern<LevelCount>::GetColors() const -> std::pair<RgbColor, RgbColor> {
        return std::make_pair(mLeft, mRight);
    }
}

#endif