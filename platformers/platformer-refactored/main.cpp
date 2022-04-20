#include "game.h"

int main (int argc, char *argv[])
{
    Game game;
    while (!WindowShouldClose())
    {
        game.Loop();
        if (IsKeyDown(KEY_Q))
        {
            return 0;
        }
    }

    return 0;
}
