#define PHYSAC_IMPLEMENTATION
#include "game.h"

int main (int argc, char *argv[])
{
    Game game;

    game.Init();
    while (!WindowShouldClose())
    {
        game.Loop();
        if (IsKeyDown(KEY_Q))
        {
            game.Close();
            return 0;
        }
    }

    return 0;
}
