#pragma once
#ifndef platform
#define platform

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
