#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <iostream>
#include <vector>
#include <algorithm>
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
    constexpr Color FG{237,237,237,255};
    constexpr Color BG{26,26,26,255};
    constexpr float PAD_W = 60.0f;
    constexpr float PAD_H = 30.0f;
    const float X_AXIS_Y = SCREEN_H - PAD_H;
    const float Y_AXIS_X = PAD_W;
    /* -------------------------------------------------------------------------- */
    /*                                SERIEST STATS                               */
    /* -------------------------------------------------------------------------- */

    struct Stats
    {
        Stats(){};
        Stats(const std::vector<float> &x, const std::vector<float> &y)
        {
            if (x.size() != y.size())
                throw std::runtime_error("Error: series sizes not the same");
            size = x.size();
            // boundaries
            max_x = *std::max_element(x.begin(), x.end());
            max_y = *std::max_element(y.begin(), y.end());
            min_x = *std::min_element(x.begin(), x.end());
            min_y = *std::min_element(y.begin(), y.end());
            // range
            range_x = max_x - min_x;
            range_y = max_y - min_y;
            // scale factors
            sf_x = (range_x != 0.0) ? (SCREEN_W) / range_x : 0.0;
            sf_y = (range_y != 0.0) ? (SCREEN_H) / range_y : 0.0;
        }
        size_t size;
        float max_x, min_x;
        float max_y, min_y;
        float range_x, range_y;
        float sf_x, sf_y;
    };
    /* -------------------------------------------------------------------------- */
    /*                                   SERIES                                   */
    /* -------------------------------------------------------------------------- */
    struct Series
    {
        Series(){};
        Series(const std::vector<float> &x, const std::vector<float> &y)
            : x(x), y(y), stats(x, y)
        {
        }
        std::vector<float> x;
        std::vector<float> y;
        Stats stats;
    };

}

#endif // PLOTTER_HPP