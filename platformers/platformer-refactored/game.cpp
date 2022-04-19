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

    camera.offset = (Vector2) {0.0f, 0.0f};
    camera.target = (Vector2) {0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

