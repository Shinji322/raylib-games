#pragma once
#define MAX_PLATFORMS 5
#ifndef map

#ifndef raylib
#include <raylib.h>
#endif // !raylib
#ifndef physac
#include "physac.h"
#endif // !physac
#ifndef cstdlib
#include <cstdlib>
#endif // ! cstdlib
#ifndef helpers
#include "helpers.h"
#endif // !helpers
#ifndef game
#include "game.h"
#endif // !game

typedef PhysicsBody Platform;

class Map
{
    private:
        Platform platforms[MAX_PLATFORMS];
        Platform ground;
        const int PLATFORM_OFFSET = 20;

        void GeneratePlatforms(int screenWidth, int screenHeight)
        {
            for (Platform platform : platforms)
            {
                float x = rand() % (screenWidth - PLATFORM_OFFSET);
                float y = rand() % (screenHeight - PLATFORM_OFFSET);
                x = clamp(x, 0.25f*screenWidth, 0.75f*screenWidth);
                y = clamp(y, 0.25f*screenHeight, 0.75f*screenHeight);

                platform->position = (Vector2) {x, y};
                platform->isGrounded = false;
                platform->useGravity = false;
            }
        }

        void GenerateGround(int screenWidth, int screenHeight)
        {
            ground->position = (Vector2) { 
                (float)screenWidth - PLATFORM_OFFSET,
                (float)screenHeight - PLATFORM_OFFSET 
            };

            ground->isGrounded = true;
            ground->useGravity = false;
        }

    public:
        Map(Game* game)
        {
            this->GeneratePlatforms(game->getScreenWidth(), game->getScreenHeight());
            this->GenerateGround(game->getScreenWidth(), game->getScreenHeight());
        }
};

#endif // !map

