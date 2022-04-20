#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#include "config.h"
#include "physac.h"

class Platform 
{
public:
    PhysicsBody body; 

    Platform() 
    {
        body = CreatePhysicsBodyRectangle(
            (Vector2){ 0, 0 },
            PLATFORM_WIDTH, PLATFORM_HEIGHT,
            PLATFORM_DENSITY
        );

        body->isGrounded = false;
        body->useGravity = false;
        body->enabled = false;
    }
};


#endif // !PLATFROM_H
