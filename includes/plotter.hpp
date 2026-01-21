#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <raylib.h>
#include <raymath.h>
#include <cstring>
#include <cmath>

namespace plt
{
    /* -------------------------------------------------------------------------- */
    /*                                  CONSTATNS                                 */
    /* -------------------------------------------------------------------------- */
    constexpr Color s = RAYWHITE;
    constexpr float SCREEN_W = 1080;
    constexpr float SCREEN_H = 720;
    constexpr float FONTSIZE = 15;
    constexpr Color FG{237, 237, 237, 255};
    constexpr Color BG{26, 26, 26, 255};
    constexpr float PAD_W = 60.0f;
    constexpr float PAD_H = 30.0f;
    const float X_AXIS_Y = SCREEN_H - PAD_H;
    const float Y_AXIS_X = PAD_W;
    constexpr size_t MAX_DATA_SIZE = 256;

}

#endif // PLOTTER_HPP