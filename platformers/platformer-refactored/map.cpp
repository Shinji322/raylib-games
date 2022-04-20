#include "map.h"
#include "config.h"
#include <raylib.h>

void Map::Draw()
{
    // Draw Platforms
    for (Platform platform : platforms) 
    {
        DrawTextureV(platformSprite, platform.body->position, LIME);
    }

    // Draw Walls
    for (Platform wall : walls)
    {
        DrawTextureV(platformSprite, wall.body->position, LIME);
    }

    // Draw Ground
    DrawTextureV(groundSprite, ground.body->position, LIME);
}

