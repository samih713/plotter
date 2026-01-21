#include "Series.hpp"

#define LOAD_CSV_H_IMPLEMENTATION
#include "load_csv.h"

// needed by load_csv
static void set_point(char **values, void *p)
{
    plt::Point *points = reinterpret_cast<plt::Point *>(p);
    points->x = atoi(values[0]);
    points->y = atoi(values[1]);
}

plt::Series::Series(const std::string &csvPath)
{
    Point points[plt::MAX_DATA_SIZE];

    config_t c{
        .n_cols = 2,
        .e_size = sizeof(Point),
        .del = ',',
        .first_row = true,
    };

    FILE *csv = load_csv(csvPath.c_str());
    size_t nCols = read_csv(csv, c, points, 10, set_point);

    x.reserve(nCols);
    y.reserve(nCols);

    for (size_t i = 0; i < nCols; ++i)
    {
        x.push_back(points[i].x);
        y.push_back(points[i].y);
    }
    this->stats.set_stats(x,y);
}