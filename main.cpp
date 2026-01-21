#include "plotter.hpp"
#include "App.hpp"

// data - original data
// world - plot (normalized) data
// screen - screen px

plt::Series to_world(const plt::Series &data)
{
    const plt::Stats &stats = data.stats;

    std::vector<float> out_x(stats.size, 0);
    std::vector<float> out_y(stats.size, 0);

    // transform
    std::transform(data.x.begin(), data.x.end(), out_x.begin(), [&stats](float x)
                   { return ((x - stats.min_x) * stats.sf_x); });
    std::transform(data.y.begin(), data.y.end(), out_y.begin(), [&stats](float y)
                   { return ((stats.max_y - y) * stats.sf_y); });

    return plt::Series(out_x, out_y); // world
}

int main()
{
    plt::App app;
    app.init();

    std::vector<float> x_input = std::vector<float>{5200, 7800, 10300, 12750, 14900, 17100, 19650, 21900, 24750, 27600};
    std::vector<float> y_input = std::vector<float>{195000, 168000, 149000, 131000, 116000, 102000, 88000, 74000, 56000, 34000};

    plt::Series data(x_input, y_input);
    plt::Series world = to_world(data);
    app.set_series(data, world);

    app.loop();

    return 0;
}
