#ifndef raylib
#include <raylib.h>
#endif // !raylib
#ifndef physac
#include "physac.h"
#endif // !physac
#include "game.h"

int Game::getScreenWidth() { return SCREEN_WIDTH; }
int Game::getScreenHeight() { return SCREEN_HEIGHT; }

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

