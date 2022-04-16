#include "helpers.h"

int clamp(int value, int min, int max)
{
    const int res = value < min ? min : value;
    return value > max ? max : res;
}
