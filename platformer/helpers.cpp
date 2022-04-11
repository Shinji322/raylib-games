#include "helpers.h"

int clamp(int value, int min, int max)
{
    // 2 lines of code that are hard to read > 3 lines of readable code 
    const int res = value < min ? min : value;
    return value > max ? max : res;
}
