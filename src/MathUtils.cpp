#include "MathUtils.h"
#include <cstdlib>

namespace MathUtils {
    float Min(float a, float b)
    {
        return a < b ? a : b;
    }

    int Min(int a, int b)
    {
        return a < b ? a : b;
    }

    float Max(float a, float b)
    {
        return a > b ? a : b;
    }

    int Max(int a, int b)
    {
        return a > b ? a : b;
    }

    float Clamp(float a, float low, float high)
    {
        return Max(low, Min(a, high));
    }

    int Clamp(int a, int low, int high) {
        return Max(low, Min(a, high));
    }

    float Lerp(float a, float b, float t) {
        return a + (b-a)*t;
    }

    float easeIn(float t) {
        return t * t;
    }

    float easeOut(float t) {
        return 1 - (1 - t) * (1 - t);
    }

    float floatRand(float min, float max)
    {
        float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
        return min + scale * (max - min);      /* [min, max] */
    }

    void int_swap(int* a, int* b) {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }

}
