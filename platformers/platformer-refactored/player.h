#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "physac.h"
#include "input.h"
#include "config.h"
#include "helpers.h"


class Player
{
private:
    // Set to fallback values in the event config.h doesn't specify
    Vector2 acceleration = (Vector2) { 1.10f, 2.0f };
    Vector2 maxVelocity = (Vector2) { 1.15f, 4.0f };
    Texture2D sprite;

    void Jump()
    {
        if (body->isGrounded == false) return;
        body->velocity.y -= acceleration.y;
        body->isGrounded = false;
    }
    void Move(Input input)
    {
        if (input.left)
            body->velocity.x = clamp_f(body->velocity.x - acceleration.x, (-1 * maxVelocity.x), 0);
        if (input.right)
            body->velocity.x = clamp_f(body->velocity.x + acceleration.x, 0, maxVelocity.x);
        if (input.up)
            Jump();
        if (input.down)
        {
            // TODO Implement Smash's Fast Fall System
            // if (body->isGrounded == false && atapexofjump)
            //     body->velocity.y += acceleration.y;
        }
    }
public:
    PhysicsBody body;

    void Init(Vector2 start_location)
    {
        body = CreatePhysicsBodyRectangle(
                start_location,
                50, 50,
                1.0f
        );
        body->isGrounded = true;
        body->useGravity = true;
        /* body->freezeOrient = true; */ 
        body->dynamicFriction = 5;
    };
    void Update(Input input);
    void Draw();
    void Close()
    {
        UnloadTexture(sprite);
    }
    void SetSprite(const char *filename)
    {
        this->sprite = LoadTexture(filename);
    }
    void SetAcceleration(Vector2 acceleration)
    {
        this->acceleration = acceleration;
    }
    void SetMaxVelocity(Vector2 maxVelocity)
    {
        this->maxVelocity = maxVelocity;
    }
    Player(){}
};

#endif // !PLAYER_H
