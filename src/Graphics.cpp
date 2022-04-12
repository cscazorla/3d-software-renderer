#include "Graphics.h"
#include "MathUtils.h"
#include <iostream>
#include <math.h>
#include <string.h>
#include <vector>
#include <stack>

SDL_Window* Graphics::window = NULL;
SDL_Renderer* Graphics::renderer = NULL;
Uint32* Graphics::color_buffer = NULL;
SDL_Texture* Graphics::color_buffer_texture = NULL;
int Graphics::window_width = 0;
int Graphics::window_height = 0;

int Graphics::Width() {
    return window_width;
}

int Graphics::Height() {
    return window_height;
}

bool Graphics::OpenWindow(int width, int height) {
    window_width = width;
    window_height = height;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL" << std::endl;
        return false;
    }

    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);
    if (!window) {
        std::cerr << "Error creating SDL window" << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer" << std::endl;
        return false;
    }

    // Allocate the required memory in bytes to hold the color buffer
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

    // Creating a SDL texture that is used to display the color buffer
    color_buffer_texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );

    SDL_WarpMouseInWindow(window, width/2, height/2);

    std::cout << "Graphics initialization called!" << std::endl;

    return true;
}

void Graphics::CloseWindow(void) {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::DrawGrid(void) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            if (x % 10 == 0 || y % 10 == 0) {
                color_buffer[(window_width * y) + x] = 0xFF444444;
            }
        }
    }
}

void Graphics::RenderFrame() {
    // Move bits from our color_buffer variable to SDL color_buffer_texture
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(window_width * sizeof(uint32_t))
    );
    // Copy a portion of the color_buffer_texture to the current rendering target.
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);

    // Clear color_buffer
    memset(color_buffer, 0, window_width * window_height * sizeof(uint32_t));

    // Swap the video buffer
    SDL_RenderPresent(renderer);
}

void Graphics::DrawPixel(int x, int y, Color color) {
    if (x >= 0 && x < window_width && y >= 0 && y < window_height) {
        if(color.r > 255 || color.g > 255 || color.b > 255)
            std::cout << "Color overflow: " << color << std::endl;
        color_buffer[(window_width * y) + x] = color.ToARGB8888();
    }
}

void Graphics::DrawLine(int x0, int y0, int x1, int y1, Color color) {
    int delta_x = (x1 - x0);
    int delta_y = (y1 - y0);

    int longest_side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

    float x_inc = delta_x / (float)longest_side_length;
    float y_inc = delta_y / (float)longest_side_length;

    float current_x = x0;
    float current_y = y0;

    for (int i = 0; i <= longest_side_length; i++) {
        DrawPixel(round(current_x), round(current_y), color);
        current_x += x_inc;
        current_y += y_inc;
    }
}

// Bresenham's (also 'Midpoint') circle algorithm
void Graphics::DrawCircle(int x0, int y0, int radius, float angle, Color color) {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        DrawPixel(x0 + x, y0 - y, color);
        DrawPixel(x0 + x, y0 + y, color);
        DrawPixel(x0 - x, y0 - y, color);
        DrawPixel(x0 - x, y0 + y, color);
        DrawPixel(x0 + y, y0 - x, color);
        DrawPixel(x0 + y, y0 + x, color);
        DrawPixel(x0 - y, y0 - x, color);
        DrawPixel(x0 - y, y0 + x, color);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

    DrawLine(x0, y0, x0 + cos(angle) * radius, y0 + sin(angle) * radius, color);
}

// Bresenham's (also 'Midpoint') circle algorithm
void Graphics::DrawFillCircle(int x0, int y0, int radius, float angle, Color color) {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        DrawLine(x0 + x, y0 - y, x0 + x, y0 + y, color);
        DrawLine(x0 - x, y0 - y, x0 - x, y0 + y, color);
        DrawLine(x0 + y, y0 - x, x0 + y, y0 + x, color);
        DrawLine(x0 - y, y0 - x, x0 - y, y0 + x, color);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
    if (angle != 0) {
        std::cout << angle << std::endl;
        DrawLine(x0, y0, x0 + cos(angle) * radius, y0 + sin(angle) * radius, Color(255, 0, 0));
    }
}

void Graphics::DrawFillCircle(int x0, int y0, int radius, Color color) {
    DrawFillCircle(x0, y0, radius, 0, color);
}

void Graphics::DrawPolygon(int x, int y, const std::vector<Vec2>& vertices, Color color) {
    for (std::size_t i = 0, max = vertices.size(); i < max; i++) {
        int currIndex = i;
        int nextIndex = (i + 1) % max;
        DrawLine(vertices[currIndex].x, vertices[currIndex].y, vertices[nextIndex].x, vertices[nextIndex].y, color);
    }
    // filledCircleColor(renderer, x, y, 1, color);
}

void Graphics::DrawRect(int x, int y, int width, int height, Color color) {
    DrawLine(x, y, x + width, y, color);
    DrawLine(x + width, y, x + width, y + height, color);
    DrawLine(x + width, y + height, x, y + height, color);
    DrawLine(x, y + height, x, y, color);
}

void Graphics::DrawFillRect(int x, int y, int width, int height, Color color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int current_x = x + i;
            int current_y = y + j;
            DrawPixel(current_x, current_y, color);
        }
    }
}

void Graphics::DrawGradRect(int x, int y, int width, int height, Color color_1, Color color_2) {
    for (int j = 0; j < height; j++) {
        float t = (float)j/height;
        Color pixel = Color::Lerp(color_1, color_2, t);
        for (int i = 0; i < width; i++) {
            int current_x = x + i;
            int current_y = y + j;
            DrawPixel(current_x, current_y, pixel);
        }
    }
}

void Graphics::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color) {
    DrawLine(x0, y0, x1, y1, color);
    DrawLine(x1, y1, x2, y2, color);
    DrawLine(x2, y2, x0, y0, color);
}

void Graphics::DrawFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color) {
    // We need to sort the vertices by y-coordinate ascending (y0 < y1 < y2)
    if (y0 > y1) {
        MathUtils::int_swap(&y0, &y1);
        MathUtils::int_swap(&x0, &x1);
    }
    if (y1 > y2) {
        MathUtils::int_swap(&y1, &y2);
        MathUtils::int_swap(&x1, &x2);
    }
    if (y0 > y1) {
        MathUtils::int_swap(&y0, &y1);
        MathUtils::int_swap(&x0, &x1);
    }

    if (y1 == y2) {
        // Draw flat-bottom triangle
        FillFlatBottomTriangle(x0, y0, x1, y1, x2, y2, color);
    } else if (y0 == y1) {
        // Draw flat-top triangle
        FillFlatTopTriangle(x0, y0, x1, y1, x2, y2, color);
    } else {
        // Calculate the new vertex (Mx,My) using triangle similarity
        int My = y1;
        int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

        // Draw flat-bottom triangle
        FillFlatBottomTriangle(x0, y0, x1, y1, Mx, My, color);

        // Draw flat-top triangle
        FillFlatTopTriangle(x1, y1, Mx, My, x2, y2, color);
    }
}

void Graphics::FillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color) {
    // Find the two slopes (two triangle legs)
    float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
    float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

    // Start x_start and x_end from the bottom vertex (x2,y2)
    float x_start = x2;
    float x_end = x2;

    // Loop all the scanlines from bottom to top
    for (int y = y2; y >= y0; y--) {
        DrawLine(x_start, y, x_end, y, color);
        x_start -= inv_slope_1;
        x_end -= inv_slope_2;
    }
}
void Graphics::FillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color color) {
    // Find the two slopes (two triangle legs)
    float inv_slope_1 = (float)(x1 - x0) / (y1 - y0);
    float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

    // Start x_start and x_end from the top vertex (x0,y0)
    float x_start = x0;
    float x_end = x0;

    // Loop all the scanlines from top to bottom
    for (int y = y0; y <= y2; y++) {
        DrawLine(x_start, y, x_end, y, color);
        x_start += inv_slope_1;
        x_end += inv_slope_2;
    }
}
