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
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 450;
        const char *title = "Shinji's Epic Platformer Test"; 
        Camera2D camera = (Camera2D) {
            (Vector2) { 0.0f, 0.0f },
            (Vector2) { 0.0f, 0.0f },
            0.0f,
            1.0f
        };
        Map map;
        Player player;


    public:
        void Init();
        void Update();
        void Draw();
        void Close();
};

#endif // ! game
