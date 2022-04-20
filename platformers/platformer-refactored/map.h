#pragma once
#ifndef MAP_H
#define MAP_H

#include <cstdlib>
#include "config.h"
#include "platform.h"
#include "helpers.h"

class Map 
{
    private:
        Platform ground;
        PhysicsBody walls[2];
        Platform platforms[MAX_PLATFORMS];
        Texture2D platformSprite;
        Texture2D groundSprite;

        void GenerateGround(Vector2 screenDimensions)
        {
            Vector2 position = (Vector2) {
                screenDimensions.x / 2,
                screenDimensions.y - 10 // Distance from below the screen
            };
        }

        void GeneratePlatforms(Vector2 screenDimensions)
        {
            // We split the entire map into sections where each platform will only be in one section
            for (int sectionWidth = (screenDimensions.x/MAX_PLATFORMS), i = 0; i < MAX_PLATFORMS; i++)
            {
                int minX = sectionWidth * i;
                int maxX = sectionWidth * (i + 1);
                int minY = 0.15f*screenDimensions.y;
                int maxY = 0.85f*screenDimensions.y;


                Vector2 position = (Vector2) {
                        clamp_f(std::rand() % maxX, minX, maxX),
                        clamp_f(std::rand() % maxY, minY, maxY)
                    };
                    
                // In the original implementation, we needed to initialize each platform related boolean to false
                // Since the class does it for us, we don't have to!
                platforms[i].body->position = position;
            }
        }

        void GenerateWalls(Vector2 screenDimensions)
        {
            walls[0] = CreatePhysicsBodyRectangle(
                (Vector2) { 0, screenDimensions.y - 10 },
                50, screenDimensions.y,
                WALL_DENSITY
            );
            walls[0]->isGrounded = false;
            walls[0]->useGravity = false;
            walls[0]->enabled = false;

            walls[1] = CreatePhysicsBodyRectangle(
                    (Vector2) { screenDimensions.x - 10, screenDimensions.x - 10 },
                    50, screenDimensions.y,
                    WALL_DENSITY
            );
            walls[1]->isGrounded = false;
            walls[1]->useGravity = false;
            walls[1]->enabled = false;
        }

    public:
        void Init(Vector2 screenDimensions)
        {
            GeneratePlatforms(screenDimensions);
            GenerateGround(screenDimensions);
            GenerateWalls(screenDimensions);

            platformSprite = LoadTexture(PLATFORM_SPRITE);
            groundSprite = LoadTexture(GROUND_SPRITE);
        }
        void Update(); 
        void Draw(); 
        void Close() 
        {
            UnloadTexture(platformSprite);
            UnloadTexture(groundSprite);
        }
        Map(){}
};


#endif // !map
