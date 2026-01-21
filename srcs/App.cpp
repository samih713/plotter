#include "plotter.hpp"
#include "App.hpp"
#include <raylib.h>

plt::App::App()
{
}

plt::App::~App()
{
    CloseWindow();
}

void plt::App::init()
{
    SetTraceLogLevel(LOG_NONE);
    InitWindow(plt::SCREEN_W, plt::SCREEN_H, "PLOTTER");
    SetTargetFPS(60);
    // init camera
    camera.target = (Vector2){plt::SCREEN_W / 2.0f, plt::SCREEN_H / 2.0f};
    camera.offset = (Vector2){plt::SCREEN_W / 2.0f, plt::SCREEN_H / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void plt::App::handle_events()
{
    // panning with keys
    if (IsKeyDown(KEY_D))
        camera.target.x += 2;
    if (IsKeyDown(KEY_A))
        camera.target.x -= 2;
    if (IsKeyDown(KEY_W))
        camera.target.y -= 2;
    if (IsKeyDown(KEY_S))
        camera.target.y += 2;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
    }
    // zoom
    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f)
    {
        // Get plot point undre mouse
        Vector2 plotPos = GetScreenToWorld2D(GetMousePosition(), camera);
        // Set off set to where mouse is
        camera.offset = GetMousePosition();
        // Set the target to match, so that the camera maps plotPos
        // to screenPos under cursor at any zoom
        camera.target = plotPos;
        // zoom
        float scale = 0.2f * wheel;
        camera.zoom = Clamp(expf(logf(camera.zoom) + scale), 0.125f, 64.0f);
    }
    if (IsKeyDown(KEY_R))
    {
        camera.target = (Vector2){plt::SCREEN_W / 2.0f, plt::SCREEN_H / 2.0f};
        camera.offset = camera.target;
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
    }
}

void plt::App::set_series(const Series &data, const Series &world)
{
    this->data = data;
    this->world = world;
}

void plt::App::loop()
{
    while (!WindowShouldClose())
    {
        handle_events();
        renderer.render(data, world, camera);
    }
}