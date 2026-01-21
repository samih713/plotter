#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "plotter.hpp"
#include "Series.hpp"

namespace plt
{
    class Renderer
    {
    public:
        Renderer() = default;
        void render(const Series &data, const Series &world, const Camera2D &camera);

    private:
        void draw_axis();
        void draw_ticks(const Stats &stats, const Camera2D &camera);
        void draw_plot(const Series &world);
        void display_coordinates(const Series &world, const Series &data);
    };
};

#endif // RENDERER_HPP