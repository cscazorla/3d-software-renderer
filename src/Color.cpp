#include "Color.h"
#include "MathUtils.h"

Color::Color(): r(0), g(0), b(0), a(255) {}
Color::Color(int r, int g, int b): r(r), g(g), b(b), a(255) {}
Color::Color(int r, int g, int b, int a): r(r), g(g), b(b), a(a) {}
Color::Color(uint32_t color) {
    r = color & 0xFF;
    g = (color >> 8) & 0xFF;
    b = (color >> 16) & 0xFF;
    a = (color >> 24) & 0xFF;
}

std::ostream& operator <<(std::ostream& os, const Color& c)
{
	os << '(' << c.r << ',' << c.g << ',' << c.b << ',' << c.a << ')';
	return os;
}

uint32_t Color::ToARGB8888() {
    uint32_t color = (a << 24) + (r << 16) + (g << 8) + b;
    return color;
}

Color Color::Darkened(float p) {
    Color res = *this;
    if (p < 0) p = 0;
    if (p > 1) p = 1;
    res.r = res.r * p;
    res.g = res.g * p;
    res.b = res.b * p;
    return res;
}

Color Color::Lightened(float p) {
    Color res = *this;
    res.r = res.r + (255 - res.r) * p;
    res.g = res.g + (255 - res.g) * p;
    res.b = res.b + (255 - res.b) * p;
    return res;
}

Color Color::ApplyFactor(float p) {
    Color res = *this;
    if (p < 0) p = 0;
    if (p > 1) p = 1;
    res.r *= p;
    res.g *= p;
    res.b *= p;
    return res;
}

Color Color::operator + (const Color& c) const {
    Color res;
    res.a = c.a;
    res.r = MathUtils::Clamp(r + c.r, 0, 255);
    res.g = MathUtils::Clamp(g + c.g, 0, 255);
    res.b = MathUtils::Clamp(b + c.b, 0, 255);
    return res;
}

Color Color::Red() {
    return Color(255, 0, 0);
}

Color Color::Green() {
    return Color(0, 255, 0);
}

Color Color::Blue() {
    return Color(0, 0, 255);
}

Color Color::Yellow() {
    return Color(255, 255, 0);
}

Color Color::White() {
    return Color(255, 255, 255);
}

Color Color::Black() {
    return Color();
}

Color Color::Lerp(Color color_1, Color color_2, float t) {
    Color result;
    result.r = MathUtils::Lerp(color_1.r, color_2.r, t);
    result.g = MathUtils::Lerp(color_1.g, color_2.g, t);
    result.b = MathUtils::Lerp(color_1.b, color_2.b, t);
    result.a = MathUtils::Lerp(color_1.a, color_2.a, t);
    return result;
}
