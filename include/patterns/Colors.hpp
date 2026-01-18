#ifndef __Colors_h__
#define __Colors_h__

#include <NeoPixelBus.h>

namespace Loml::Colors {
    // Pinks & Pinkish-Purples
    constexpr inline RgbColor HotPink{255, 105, 180};
    constexpr inline RgbColor Fuchsia{255, 0, 255};
    constexpr inline RgbColor Raspberry{227, 11, 92};
    constexpr inline RgbColor DarkPink{170, 51, 106};
    constexpr inline RgbColor SteelPink{204, 51, 102};
    constexpr inline RgbColor Rose{243, 58, 106};
    constexpr inline RgbColor Magenta{255, 0, 255};

    // Purples & Purple-Pinks
    constexpr inline RgbColor Purple{128, 0, 128};
    constexpr inline RgbColor Lavender{230, 230, 250};
    constexpr inline RgbColor LightPurple{203, 195, 227};
    constexpr inline RgbColor Mauve{224, 176, 255};
    constexpr inline RgbColor Orchid{218, 112, 214};
    constexpr inline RgbColor Iris{93, 63, 211};
    constexpr inline RgbColor Periwinkle{204, 204, 255};
    constexpr inline RgbColor Plum{103, 49, 71};
    constexpr inline RgbColor PurplePlum{156, 81, 182};

    // Blended/Unique Shades
    constexpr inline RgbColor BrilliantLavender{255, 189, 247};
    constexpr inline RgbColor VioletPink{238, 130, 238};
    constexpr inline RgbColor LightDeepPink{255, 92, 204};
}

#endif