#include "player.h"
#include <raylib.h>
#include "physac.h"

void Player::Draw()
{
    // MAYBE_TODO Implement animations using a spritesheet?
    // NOTE This might not work due to sprite position and texture positioning being different
    // i.e. texture might draw from middle whereas body position is at the top
    DrawTextureV(sprite, body->position, LIME);
}


void Player::Update(Input input)
{
    Move(input);    
}
