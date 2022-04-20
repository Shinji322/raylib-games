#pragma once
#ifndef CONFIG_H
#define CONFIG_H
#include <raylib.h>

// General
const Vector2 PLAYER_ACCELERATION = (Vector2) { 1.10f, 2.0f };
const Vector2 MAX_VELOCITY = (Vector2) { 1.15f, 4.0f };
const Vector2 GRAVITY = (Vector2) { 0.0f, 9.81f };
const char PLAYER_SPRITE[] = "assets/Retro-Mario-2-icon.bmp";
const char PLATFORM_SPRITE[] = "assets/platform.bmp";
const char GROUND_SPRITE[] = "assets/platform.bmp";
const int CONFIG_FLAGS = FLAG_MSAA_4X_HINT;
#define MAX_PLATFORMS 5
#define PLATFORM_WIDTH 50
#define PLATFORM_HEIGHT 20

// Specific Physics Related Stuff
#define PLATFORM_DENSITY 1
#define WALL_DENSITY 1


#endif //!CONFIG_H
