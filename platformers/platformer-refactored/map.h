#pragma once
#ifndef MAP_H
#define MAP_H

#include "config.h"
#include <cstdlib>
#include "physac.h"
#include "platform.h"
#include "helpers.h"

class Map 
{
    private:
        Platform ground;
        Platform walls[2];
        Platform platforms[MAX_PLATFORMS];

        void GenerateGround(Vector2 screenDimensions)
        {
            Vector2 position = (Vector2) {
                screenDimensions.x / 2,
                screenDimensions.y - 10 // Distance from below the screen
            };
        }

        void GeneratePlatforms(Vector2 screenDimensions)
        {
            for (int i = 0; i < MAX_PLATFORMS; i++)
            {
                int minX = (screenDimensions.x) / (MAX_PLATFORMS - i);
                int maxX = (screenDimensions.x) / (MAX_PLATFORMS - i + 1);
                int minY = 0.15f*screenDimensions.y;
                int maxY = 0.85f*screenDimensions.y;


                Vector2 position = (Vector2) {
                        clamp_f(std::rand() % maxX, minX, maxX),
                        clamp_f(std::rand() % maxY, minY, maxY)
                    };
                    
                // In the original implementation, we needed to initialize each platform related boolean to false
                // Since the class does it for us, we don't have to!
                platforms[i].body = CreatePhysicsBodyRectangle(
                            position,
                            PLATFORM_WIDTH, PLATFORM_HEIGHT,
                            PLATFORM_DENSITY
                        );
            }
        }

        void GenerateWalls(Vector2 screenDimensions)
        {
            walls[0].body = CreatePhysicsBodyRectangle(
                (Vector2) { 0, screenDimensions.y - 10 },
                50, screenDimensions.y,
                WALL_DENSITY
            );
            walls[0].body->isGrounded = false;
            walls[0].body->useGravity = false;
            walls[0].body->enabled = false;

            walls[1].body = CreatePhysicsBodyRectangle(
                    (Vector2) { screenDimensions.x - 10, screenDimensions.x - 10 },
                    50, screenDimensions.y,
                    WALL_DENSITY
            );
            walls[1].body->isGrounded = false;
            walls[1].body->useGravity = false;
            walls[1].body->enabled = false;
        }

    public:
        void Init(Vector2 screenDimensions)
        {
            GeneratePlatforms(screenDimensions);
            GenerateGround(screenDimensions);
            GenerateWalls(screenDimensions);
        }
        void Update(); // TODO implemented by game
        void Draw(); // TODO implemented in game
        void Close();
        Map(){}
};


#endif // !map
