#include "helpers.h"

float abs_f(float value)
{
    return (value < 0) ? (value * -1) : (value);
}

int abs(int value)
{
    return (value < 0) ? (value * -1) : (value);
}

int clamp(int value, int min, int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

float clamp_f(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
