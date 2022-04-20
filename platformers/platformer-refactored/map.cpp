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
    for (PhysicsBody wall : walls)
    {
        DrawTextureV(platformSprite, wall->position, LIME);
    }

    // Draw Ground
    DrawTextureV(groundSprite, ground.body->position, LIME);
}

void Map::Update()
{

}
