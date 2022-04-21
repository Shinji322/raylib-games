#include "helpers.h"
#include "config.def.h"
#include <time.h>

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

#ifdef WINDOWS
#include <windows.h>

void delay(float seconds)
{ 
    // Arg is millesconds
    Sleep((int)(1000 * seconds));
}
#endif

#ifdef UNIX
#include <unistd.h> 

void delay(float seconds)
{
    unsigned int microsecond = 1000000;
    sleep((int)(seconds * microsecond));
}
#endif
