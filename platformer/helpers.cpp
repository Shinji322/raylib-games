#include "helpers.h"

int clamp(int value, int min, int max)
{
    // Screw it this makes more sense
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
