#include "player.h"

#include <raylib.h>
#include "physac.h"

void Player::Init(Vector2 start_location)
{
    body = CreatePhysicsBodyRectangle(
            start_location,
            50, 50,
            1.0f
        );
    
    body->isGrounded = true;
    body->useGravity = true;
    // body->freezeOrient = true;
    body->dynamicFriction = 5;
}


void Player::Draw(Vector2 position)
{
    // MAYBE_TODO Implement animations using a spritesheet?
    DrawTexture(sprite, position.x, position.y, LIME);
}


void Player::Update()
{
    
}


void Player::Close()
{
    UnloadTexture(sprite);
}
