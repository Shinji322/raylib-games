#include <raylib.h>
#include "physac.h"
#include "config.h"
#include "game.h"

void Game::Init()
{
    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        title
    );

    SetPhysicsGravity(GRAVITY.x, GRAVITY.y);

}
