#pragma once
#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "config.h"
#include "map.h"
#include "player.h"


class Game 
{
    private:
        const Vector2 SCREEN_DIMENSIONS = (Vector2) { 800, 450 };
        const char *title = "Shinji's Epic Platformer Test"; 
        Camera2D camera = (Camera2D) {
            (Vector2) { 0.0f, 0.0f },
            (Vector2) { 0.0f, 0.0f },
            0.0f,
            1.0f
        };
        Map map;
        Player player;
        InputManager inputManager;


    public:
        void Init();
        void Update();
        void Draw();
        void Close();
        void Loop();
};

#endif // ! GAME_H
