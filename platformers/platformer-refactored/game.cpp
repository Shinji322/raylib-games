#include <raylib.h>
#include "physac.h"
#include "config.h"
#include "game.h"
#define PHYSAC_IMPLEMENTATION

void Game::Init()
{
    InitWindow(
        SCREEN_DIMENSIONS.x,
        SCREEN_DIMENSIONS.y,
        title
    );

    InitPhysics();
    SetPhysicsGravity(GRAVITY.x, GRAVITY.y);

    SetTargetFPS(60);

    map.Init(SCREEN_DIMENSIONS);
    player.Init((Vector2){
        SCREEN_DIMENSIONS.x / 2,
        SCREEN_DIMENSIONS.y - 15
    });
    player.SetSprite(PLAYER_SPRITE);
    player.SetAcceleration(PLAYER_ACCELERATION);
    player.SetMaxVelocity(MAX_VELOCITY);
}

void Game::Close()
{
    player.Close();
    map.Close();
    EndDrawing();
    ClosePhysics();
}

void Game::Update()
{
    player.Update(inputManager.checkUserInput());
    map.Update();
    UpdatePhysics();
}

void Game::Draw()
{
    BeginDrawing();
        // TODO Implement these methods
        player.Draw();
        map.Draw();
    EndDrawing();
}

void Game::Loop()
{
    Update();
    Draw();
}
