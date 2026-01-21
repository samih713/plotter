#include "Renderer.hpp"

void plt::Renderer::render(const plt::Series &data, const plt::Series &world, const Camera2D &camera)
{
    BeginDrawing();
    ClearBackground(plt::BG);
    draw_axis();
    draw_ticks(data.stats, camera);
    BeginMode2D(camera);
    DrawCircleV(camera.target, 5, RED);
    draw_plot(world);
    display_coordinates(world, data);
    EndMode2D();
    EndDrawing();
}

void plt::Renderer::draw_axis()
{
    // draw x-axis
    Vector2 x_axis_start{0, plt::X_AXIS_Y};
    Vector2 x_axis_end{plt::SCREEN_W, plt::X_AXIS_Y};
    DrawLineV(x_axis_start, x_axis_end, plt::FG);
    // draw y-axis
    Vector2 y_axis_start{plt::Y_AXIS_X, 0};
    Vector2 y_axis_end{plt::Y_AXIS_X, plt::SCREEN_H};
    DrawLineV(y_axis_start, y_axis_end, plt::FG);
}

void plt::Renderer::draw_ticks(const plt::Stats &dStats, const Camera2D &camera)
{
    constexpr float pxStep = 120.0f; // desired spacing between ticks in pixels
    constexpr float tickLen = 10.0f;
    constexpr float labelPad = 3.0f;
    const float plotStep = pxStep / camera.zoom;
    char buf[64];
    /* ----------------------------- PLOT BOUNDARIES ---------------------------- */
    const float plotLeft = GetScreenToWorld2D({0.0f, plt::X_AXIS_Y}, camera).x;
    const float plotRight = GetScreenToWorld2D({plt::SCREEN_W, plt::X_AXIS_Y}, camera).x;
    const float plotTop = GetScreenToWorld2D({plt::Y_AXIS_X, 0.0f}, camera).y;
    const float plotBottom = GetScreenToWorld2D({plt::Y_AXIS_X, (float)plt::SCREEN_H}, camera).y;
    /* ------------------------------- FIXED AXIS ------------------------------- */
    const float plotXaxisY = GetScreenToWorld2D({0.0f, plt::X_AXIS_Y}, camera).y;
    const float plotYaxisX = GetScreenToWorld2D({plt::Y_AXIS_X, 0.0f}, camera).x;

    /* ------------------- ---------- X AXIS TICKS ---------- ------------------- */
    {
        float a = std::min(plotLeft, plotRight);
        float b = std::max(plotLeft, plotRight);

        float t = std::floor(a / plotStep) * plotStep;

        for (; t <= b; t += plotStep)
        {
            float screenX = GetWorldToScreen2D({t, plotXaxisY}, camera).x;

            // tick mark on x-axis (fixed screen plt::X_AXIS_Y)
            DrawLineV({screenX, plt::X_AXIS_Y - tickLen}, {screenX, plt::X_AXIS_Y + tickLen}, plt::FG);

            // label
            std::snprintf(buf, sizeof(buf), "%.0f", (t / dStats.sf_x) + dStats.min_x);
            int tw = MeasureText(buf, plt::FONTSIZE);
            DrawText(buf, (int)(screenX - tw * 0.5f), (int)(plt::X_AXIS_Y + tickLen + labelPad), plt::FONTSIZE, plt::FG);
        }
    }
    /* ------------------- ---------- Y AXIS TICKS ---------- ------------------- */
    {
        float a = std::min(plotTop, plotBottom);
        float b = std::max(plotTop, plotBottom);

        float t = std::floor(a / plotStep) * plotStep;

        for (; t <= b; t += plotStep)
        {
            float screenY = GetWorldToScreen2D({plotYaxisX, t}, camera).y;

            // tick mark on y-axis (fixed screen plt::Y_AXIS_X)
            DrawLineV({plt::Y_AXIS_X - tickLen, screenY}, {plt::Y_AXIS_X + tickLen, screenY}, plt::FG);

            // label (to the left of the y-axis)
            std::snprintf(buf, sizeof(buf), "%.0f", dStats.max_y - (t / dStats.sf_y));
            int tw = MeasureText(buf, plt::FONTSIZE);
            DrawText(buf, (int)(plt::Y_AXIS_X - tickLen - labelPad - tw), (int)(screenY - plt::FONTSIZE * 0.5f), plt::FONTSIZE, plt::FG);
        }
    }
}

void plt::Renderer::draw_plot(const plt::Series &world)
{
    constexpr float radius = 4;

    Vector2 center;
    for (size_t i = 0; i < world.stats.size; ++i)
    {
        center = {
            .x = world.x.at(i),
            .y = world.y.at(i)};

        DrawCircleV(center, radius, plt::FG);
    }
}

void plt::Renderer::display_coordinates(const plt::Series &world, const plt::Series &data)
{
    constexpr float offset = 5;

    char buffer[64];
    Vector2 pos;
    for (size_t i = 0; i < world.stats.size; ++i)
    {
        pos =
            {
                .x = world.x.at(i) + offset,
                .y = world.y.at(i) + offset};

        snprintf(buffer, sizeof(buffer), "(%.0f,%.0f)", data.x.at(i), data.y.at(i));
        DrawText(buffer, pos.x, pos.y, plt::FONTSIZE, plt::FG);
    }
}