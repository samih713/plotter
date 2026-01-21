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

    plt::Series data("./data/data.csv");
    plt::Series world = to_world(data);
    app.set_series(data, world);

    app.loop();

    return 0;
}
