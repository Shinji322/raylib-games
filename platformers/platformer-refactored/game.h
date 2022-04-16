#pragma once
#ifndef game

#ifndef raylib
#include <raylib.h>
#endif // !raylib


class Game 
{
    private:
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 450;
        const Vector2 GRAVITY = { 0.0f, 9.81f };
        const char *title = "Shinji's Epic Platformer Test"; 
        Camera2D camera = (Camera2D) { (Vector2) {} };

    public:
        void Init();
        int getScreenWidth();
        int getScreenHeight();
};

#endif // ! game
