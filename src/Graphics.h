#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <vector>
#include "Color.h"
#include "Vec2.h"

class Graphics {
    private:
        static int window_width;
        static int window_height;
        static SDL_Window* window;
        static SDL_Renderer* renderer;
        static Uint32* color_buffer;
        static SDL_Texture* color_buffer_texture;

        static void FillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);
        static void FillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);

        static void DrawFPSDigit(int digit, int x_start, int y_start, int size, Color color);

    public:
        static int Width();
        static int Height();

        static bool OpenWindow(int width, int height);
        static void CloseWindow();
        static void RenderFrame();

        static void DrawGrid(void);

        static void DrawPixel(int x, int y, Color color);
        static void DrawLine(int x0, int y0, int x1, int y1, Color color);
        static void DrawCircle(int x, int y, int radius, float angle, Color color);
        static void DrawFillCircle(int x, int y, int radius, Color color);
        static void DrawFillCircle(int x, int y, int radius, float angle, Color color);
        static void DrawPolygon(int x, int y, const std::vector<Vec2>& vertices, Color color);
        static void DrawRect(int x, int y, int width, int height, Color color);
        static void DrawFillRect(int x, int y, int width, int height, Color color);
        static void DrawGradRect(int x, int y, int width, int height, Color color_1, Color color_2);
        static void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);
        static void DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color);

};

#endif
