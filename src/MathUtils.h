#ifndef MATH_UTILS_H
#define MATH_UTILS_H

namespace MathUtils {
    float Min(float a, float b);
    float Max(float a, float b);
    float Clamp(float a, float low, float high);
    int Min(int a, int b);
    int Max(int a, int b);
    int Clamp(int a, int low, int high);
    float Lerp(float a, float b, float t);
    float easeIn(float t);
    float easeOut(float t);
    float floatRand(float min, float max);
    void int_swap(int* a, int* b);
}

#endif
