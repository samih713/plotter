#ifndef APP_HPP
#define APP_HPP

#include "plotter.hpp"
#include "Renderer.hpp"

namespace plt
{
    class App
    {
    public:
        App();
        ~App();

        void init();
        void set_series(const Series &data, const Series &plot);
        void loop();
        void handle_events();

    private:
        Camera2D camera;
        Renderer renderer;
        Series data, world;
    };
}

#endif // APP_HPP