#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#include "physac.h"

class Platform 
{
public:
    PhysicsBody body;

    Platform() 
    {
        body->isGrounded = false;
        body->useGravity = false;
        body->enabled = false;
    }
};


#endif // !platform
