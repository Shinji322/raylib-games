#include "helpers.h"
#include <iostream>

float abs(float value)
{
    return (value < 0) ? (value * -1) : (value);
}

int abs(int value)
{
    return (value < 0) ? (value * -1) : (value);
}

int clamp(int value, int min, int max)
{
    // Screw it this makes more sense
    std::cout << "Clamping " << value << ", Min" << min << ", Max" << max << std::endl;
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

float clamp(float value, float min, float max)
{
    std::cout << "Clamping " << value << ", Min" << min << ", Max" << max << std::endl;
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
