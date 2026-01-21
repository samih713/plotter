#ifndef SERIES_HPP
#define SERIES_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <string>

#include "plotter.hpp"

namespace plt
{
    struct Point
    {
        size_t x;
        size_t y;
    };

    struct Stats
    {
        Stats() {};
        Stats(const std::vector<float> &x, const std::vector<float> &y)
        {
            set_stats(x, y);
        }

        void set_stats(const std::vector<float> &x, const std::vector<float> &y)
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

    struct Series
    {
        Series() {};
        Series(const std::vector<float> &x, const std::vector<float> &y)
            : x(x), y(y), stats(x, y)
        {
        }
        Series(const std::string &csvPath);
        std::vector<float> x;
        std::vector<float> y;
        Stats stats;
    };
}

#endif // SERIES_HPP