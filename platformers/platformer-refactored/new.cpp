#include <cstdlib> // for rng 
#include <raylib.h> // for graphical rendering
#include "game.h"
#include "physac.h" // for physics
#include "helpers.h" // for various helper functions

#define MAX_PLATFORMS 5

//---------------------------------------------------------//
// Class declarations                                      //
//---------------------------------------------------------//
// For clarity
typedef PhysicsBody Platform;

// Stores all of the platforms and their locations
class Map
{
    private:
        Platform platforms[MAX_PLATFORMS];
        Platform ground;
        const int PLATFORM_OFFSET = 20;

        void GeneratePlatforms(int screenWidth, int screenHeight)
        {
            for (Platform platform : platforms)
            {
                float x = rand() % (screenWidth - PLATFORM_OFFSET);
                float y = rand() % (screenHeight - PLATFORM_OFFSET);
                x = clamp(x, 0.25f*screenWidth, 0.75f*screenWidth);
                y = clamp(y, 0.25f*screenHeight, 0.75f*screenHeight);

                platform->position = (Vector2) {x, y};
                platform->isGrounded = false;
                platform->useGravity = false;
            }
        }

        void GenerateGround(int screenWidth, int screenHeight)
        {
            ground->position = (Vector2) { 
                (float)screenWidth - PLATFORM_OFFSET,
                (float)screenHeight - PLATFORM_OFFSET 
            };

            ground->isGrounded = true;
            ground->useGravity = false;
        }

    public:
        Map(Game* game)
        {
            this->GeneratePlatforms(game->getScreenWidth(), game->getScreenHeight());
            this->GenerateGround(game->getScreenWidth(), game->getScreenHeight());
        }
};


class Player
{
    private:
        PhysicsBody body;

    public:
        Player()
        {

        }
};


int main (int argc, char *argv[])
{
    Player player;
    Game game;

    return 0;
}
