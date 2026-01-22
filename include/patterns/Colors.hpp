#ifndef Colors_h_
#define Colors_h_

#include <NeoPixelBus.h>

namespace Loml::Colors {
    // Grayscale
    constexpr inline RgbColor Black{0, 0, 0};
    constexpr inline RgbColor DarkGray{64, 64, 64};
    constexpr inline RgbColor Gray{128, 128, 128};
    constexpr inline RgbColor LightGray{192, 192, 192};
    constexpr inline RgbColor White{255, 255, 255};

    // Reds
    constexpr inline RgbColor Red{255, 0, 0};
    constexpr inline RgbColor DarkRed{139, 0, 0};
    constexpr inline RgbColor Crimson{220, 20, 60};
    constexpr inline RgbColor IndianRed{205, 92, 92};
    constexpr inline RgbColor LightCoral{240, 128, 128};
    constexpr inline RgbColor Salmon{250, 128, 114};
    constexpr inline RgbColor DarkSalmon{233, 150, 122};
    constexpr inline RgbColor LightSalmon{255, 160, 122};
    constexpr inline RgbColor Tomato{255, 99, 71};
    constexpr inline RgbColor OrangeRed{255, 69, 0};
    constexpr inline RgbColor FireBrick{178, 34, 34};
    constexpr inline RgbColor Coral{255, 127, 80};
    constexpr inline RgbColor Scarlet{255, 36, 0};
    constexpr inline RgbColor Maroon{128, 0, 0};

    // Oranges
    constexpr inline RgbColor Orange{255, 165, 0};
    constexpr inline RgbColor DarkOrange{255, 140, 0};
    constexpr inline RgbColor LightOrange{255, 200, 124};
    constexpr inline RgbColor Tangerine{242, 133, 0};
    constexpr inline RgbColor PeachOrange{255, 184, 82};
    constexpr inline RgbColor Apricot{251, 206, 177};
    constexpr inline RgbColor SandyBrown{244, 164, 96};
    constexpr inline RgbColor Chocolate{210, 105, 30};
    constexpr inline RgbColor DarkGoldenrod{184, 134, 11};
    constexpr inline RgbColor Goldenrod{218, 165, 32};
    constexpr inline RgbColor Gold{255, 215, 0};

    // Yellows
    constexpr inline RgbColor Yellow{255, 255, 0};
    constexpr inline RgbColor LightYellow{255, 255, 224};
    constexpr inline RgbColor LemonChiffon{255, 250, 205};
    constexpr inline RgbColor Khaki{240, 230, 140};
    constexpr inline RgbColor DarkKhaki{189, 183, 107};
    constexpr inline RgbColor PaleGoldenrod{238, 232, 170};
    constexpr inline RgbColor Olive{128, 128, 0};
    constexpr inline RgbColor OliveDrab{107, 142, 35};

    // Greens
    constexpr inline RgbColor Green{0, 128, 0};
    constexpr inline RgbColor DarkGreen{0, 100, 0};
    constexpr inline RgbColor ForestGreen{34, 139, 34};
    constexpr inline RgbColor LimeGreen{50, 205, 50};
    constexpr inline RgbColor Lime{0, 255, 0};
    constexpr inline RgbColor SpringGreen{0, 255, 127};
    constexpr inline RgbColor PaleGreen{152, 251, 152};
    constexpr inline RgbColor LightGreen{144, 238, 144};
    constexpr inline RgbColor MediumSpringGreen{0, 250, 154};
    constexpr inline RgbColor MediumAquamarine{102, 205, 170};
    constexpr inline RgbColor Aquamarine{127, 255, 212};
    constexpr inline RgbColor SeaGreen{46, 139, 87};
    constexpr inline RgbColor DarkSeaGreen{143, 188, 143};
    constexpr inline RgbColor LightSeaGreen{32, 178, 170};
    constexpr inline RgbColor MediumSeaGreen{60, 179, 113};

    // Cyans & Teals
    constexpr inline RgbColor Cyan{0, 255, 255};
    constexpr inline RgbColor Aqua{0, 255, 255};
    constexpr inline RgbColor LightCyan{224, 255, 255};
    constexpr inline RgbColor PaleTurquoise{175, 238, 238};
    constexpr inline RgbColor Turquoise{64, 224, 208};
    constexpr inline RgbColor MediumTurquoise{72, 209, 204};
    constexpr inline RgbColor DarkTurquoise{0, 206, 209};
    constexpr inline RgbColor Teal{0, 128, 128};
    constexpr inline RgbColor DarkCyan{0, 139, 139};

    // Blues
    constexpr inline RgbColor Blue{0, 0, 255};
    constexpr inline RgbColor DarkBlue{0, 0, 139};
    constexpr inline RgbColor MidnightBlue{25, 25, 112};
    constexpr inline RgbColor Navy{0, 0, 128};
    constexpr inline RgbColor RoyalBlue{65, 105, 225};
    constexpr inline RgbColor CornflowerBlue{100, 149, 237};
    constexpr inline RgbColor SteelBlue{70, 130, 180};
    constexpr inline RgbColor LightSteelBlue{176, 196, 222};
    constexpr inline RgbColor SlateBlue{106, 90, 205};
    constexpr inline RgbColor MediumSlateBlue{123, 104, 238};
    constexpr inline RgbColor MediumBlue{0, 0, 205};
    constexpr inline RgbColor LightBlue{173, 216, 230};
    constexpr inline RgbColor SkyBlue{135, 206, 235};
    constexpr inline RgbColor LightSkyBlue{135, 206, 250};
    constexpr inline RgbColor DeepSkyBlue{0, 191, 255};
    constexpr inline RgbColor DodgerBlue{30, 144, 255};
    constexpr inline RgbColor PowderBlue{176, 224, 230};

    // Purples & Violets
    constexpr inline RgbColor Purple{128, 0, 128};
    constexpr inline RgbColor DarkViolet{148, 0, 211};
    constexpr inline RgbColor BlueViolet{138, 43, 226};
    constexpr inline RgbColor Indigo{75, 0, 130};
    constexpr inline RgbColor MediumPurple{147, 112, 219};
    constexpr inline RgbColor SlateGray{112, 128, 144};
    constexpr inline RgbColor MediumSlateBlue2{123, 104, 238};
    constexpr inline RgbColor Violet{238, 130, 238};
    constexpr inline RgbColor Plum{221, 160, 221};
    constexpr inline RgbColor Thistle{216, 191, 216};
    constexpr inline RgbColor DarkPlum{51, 0, 51};
    constexpr inline RgbColor Lavender{230, 230, 250};
    constexpr inline RgbColor Orchid{218, 112, 214};
    constexpr inline RgbColor MediumOrchid{186, 85, 211};
    constexpr inline RgbColor DarkOrchid{153, 50, 204};

    // Pinks & Magentas
    constexpr inline RgbColor HotPink{255, 105, 180};
    constexpr inline RgbColor DeepPink{255, 20, 147};
    constexpr inline RgbColor Magenta{255, 0, 255};
    constexpr inline RgbColor Fuchsia{255, 0, 255};
    constexpr inline RgbColor Pink{255, 192, 203};
    constexpr inline RgbColor LightPink{255, 182, 193};
    constexpr inline RgbColor PaleVioletRed{219, 112, 147};
    constexpr inline RgbColor VioletRed{208, 32, 144};
    constexpr inline RgbColor MediumVioletRed{199, 21, 133};
    constexpr inline RgbColor Raspberry{227, 11, 92};
    constexpr inline RgbColor Rose{243, 58, 106};
    constexpr inline RgbColor DarkPink{170, 51, 106};

    // Browns & Tans
    constexpr inline RgbColor Brown{165, 42, 42};
    constexpr inline RgbColor SaddleBrown{139, 69, 19};
    constexpr inline RgbColor Sienna{160, 82, 45};
    constexpr inline RgbColor Peru{205, 133, 63};
    constexpr inline RgbColor Tan{210, 180, 140};
    constexpr inline RgbColor Burlywood{222, 184, 135};
    constexpr inline RgbColor Bisque{255, 228, 196};
    constexpr inline RgbColor Wheat{245, 245, 220};
    constexpr inline RgbColor Moccasin{255, 228, 181};
    constexpr inline RgbColor NavajoWhite{255, 222, 173};

    // Pastels & Light Shades
    constexpr inline RgbColor MistyRose{255, 228, 225};
    constexpr inline RgbColor AntiqueWhite{250, 235, 215};
    constexpr inline RgbColor BlanchedAlmond{255, 235, 205};
    constexpr inline RgbColor AliceBlue{240, 248, 255};
    constexpr inline RgbColor GhostWhite{248, 248, 255};
    constexpr inline RgbColor Lavender2{230, 230, 250};
    constexpr inline RgbColor Honeydew{240, 255, 240};
    constexpr inline RgbColor MintCream{245, 255, 250};
    constexpr inline RgbColor Azure{240, 255, 255};
    constexpr inline RgbColor Linen{250, 240, 230};
    constexpr inline RgbColor Floral{255, 250, 240};
    constexpr inline RgbColor Seashell{255, 245, 238};
    constexpr inline RgbColor OldLace{253, 245, 230};
    constexpr inline RgbColor Papaya{255, 239, 213};
    constexpr inline RgbColor Beige{245, 245, 220};

    // Dark Shades
    constexpr inline RgbColor MidnightBlue2{25, 25, 112};
    constexpr inline RgbColor DarkGoldenrod2{184, 134, 11};
    constexpr inline RgbColor DarkSlateBlue{72, 61, 139};
    constexpr inline RgbColor DarkSlateGray{47, 79, 79};

    // Vibrant/Neon-like
    constexpr inline RgbColor NeonPink{255, 16, 240};
    constexpr inline RgbColor NeonGreen{57, 255, 20};
    constexpr inline RgbColor NeonBlue{0, 255, 127};
    constexpr inline RgbColor NeonCyan{0, 255, 255};
    constexpr inline RgbColor ElectricBlue{0, 165, 255};
    constexpr inline RgbColor ElectricGreen{0, 255, 0};
    constexpr inline RgbColor ElectricPurple{191, 64, 191};
    constexpr inline RgbColor LimeYellow{50, 205, 50};
}

#endif