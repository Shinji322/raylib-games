#include <cstdlib> // for rng 
#include <iostream>
#include <raylib.h> // for graphical rendering

#define PHYSAC_IMPLEMENTATION
#include "physac.h" // for physics
#include "helpers.h" // for various helper functions

#define CONSOLE_LOGGING // logs info to console
// #define CONSOLE_LOGGING_UPDATE // logs info on every update call

#define MAX_PLATFORMS 5
#define PHYSICS_ENABLED false
const Vector2 VELOCITY = (Vector2) { 1.0f, 1.0f };
const Vector2 ACCELERATION = (Vector2) { 1.0f, 1.0f };

//---------------------------------------------------------//
// Class declarations                                      //
//---------------------------------------------------------//
typedef struct Input
{
    bool left;
    bool right;
    bool down;
    bool up;
    bool jump;
} Input;
// For clarity
typedef PhysicsBody Platform;
// Stores all of the platforms and their locations
class Map
{
    private:
        Platform platforms[MAX_PLATFORMS];
        const int PLATFORM_OFFSET = 20;

        void GeneratePlatforms(int screenWidth, int screenHeight)
        {
            #ifdef CONSOLE_LOGGING
                std::cout << "Generating platforms" << std::endl;     
            #endif // CONSOLE_LOGGING

            for (Platform platform : platforms)
            {
                float x = std::rand() % (screenWidth - PLATFORM_OFFSET);
                float y = std::rand() % (screenHeight - PLATFORM_OFFSET);
                x = clamp(x, 0.25f*screenWidth, 0.75f*screenWidth);
                y = clamp(y, 0.25f*screenHeight, 0.75f*screenHeight);

                float width = std::rand() % (screenWidth / 3);
                float height = std::rand() % (screenHeight / 3);

                platform = CreatePhysicsBodyRectangle(
                        (Vector2) {x, y},
                        width, height,
                        1
                );
                platform->isGrounded = false;
                platform->useGravity = false;
                platform->enabled = PHYSICS_ENABLED;
            }
        }

        Platform GenerateGround(int screenWidth, int screenHeight)
        {
            #ifdef CONSOLE_LOGGING
                std::cout << "Generating ground" << std::endl;     
            #endif // CONSOLE_LOGGING

            Vector2 position = (Vector2) {
                (float)screenWidth - PLATFORM_OFFSET,
                (float)PLATFORM_OFFSET 
            };

            Platform ground = CreatePhysicsBodyRectangle(
                    position,
                    screenWidth - PLATFORM_OFFSET, 10, 
                    1
            );

            ground->isGrounded = true;
            ground->useGravity = false;
            ground->enabled = PHYSICS_ENABLED;

            return ground;
        }

    public:
        Platform ground;

        void Init(int SCREEN_WIDTH, int SCREEN_HEIGHT)
        {
            #ifdef CONSOLE_LOGGING
                std::cout << "Intializing map" << std::endl;     
            #endif // CONSOLE_LOGGING

            GeneratePlatforms(SCREEN_WIDTH, SCREEN_HEIGHT);
            ground = GenerateGround(SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        Map()
        {
            #ifdef CONSOLE_LOGGING
                std::cout << "Creating map" << std::endl;     
            #endif // CONSOLE_LOGGING
        }
};

class Player
{
    private:
        PhysicsBody body;

    public:
        void Init(Vector2 groundPosition)
        {
            #ifdef CONSOLE_LOGGING
                std::cout << "Initializing player" << std::endl;     
            #endif // CONSOLE_LOGGING

            // TODO investigate why the program is sticking here
            Vector2 position = (Vector2) {
                groundPosition.x / 2.0f,
                groundPosition.y + 10,
            };

            body = CreatePhysicsBodyRectangle(
                position,   
                50, 50,
                1.0f
            );

            body->isGrounded = true;
            body->useGravity = true;
            body->freezeOrient = true;
        }

        void Jump()
        {
            #ifdef CONSOLE_LOGGING
                std::cout << "Jumping" << std::endl;     
            #endif // CONSOLE_LOGGING

            if (body->isGrounded == false) return;
            body->velocity.y += ACCELERATION.y;
            body->isGrounded = false;
        }

        void Move(Input input)
        {
            #ifdef CONSOLE_LOGGING_UPDATE
                std::cout << "Moving" << std::endl;     
            #endif // CONSOLE_LOGGING

            if (input.left)
                body->velocity.x -= ACCELERATION.x;
            if (input.right)
                body->velocity.x += ACCELERATION.x;
            if (input.down)
            {
                // TODO Implement a function similar to Smash's fast fall system
                body->velocity.y -= ACCELERATION.y;
            }
            if (input.up)
            {
                
            }
            if (input.jump)
                Jump();
        }


        Player()
        {
            #ifdef CONSOLE_LOGGING
                std::cout << "Creating player" << std::endl;     
            #endif // CONSOLE_LOGGING
        }
};

class Game
{
    private:
        const int SCREEN_WIDTH = 800;
        const int SCREEN_HEIGHT = 450;
        const int CONFIG_FLAGS = FLAG_MSAA_4X_HINT;
        const Vector2 GRAVITY = { 0.0f, 9.81f };
        const char *title = "Shinji's Epic Platformer Test"; 
        Camera2D camera = (Camera2D) { 
            (Vector2) {0.0f, 0.0f}, 
            (Vector2) {0.0f, 0.0f},
            0.0f,
            1.0f
        };
        Map gameMap;
        Player player;

    public:
        void Init()
        {
            #ifdef CONSOLE_LOGGING
                std::cout << "Initializing game" << std::endl;     
            #endif // CONSOLE_LOGGING

            SetConfigFlags(CONFIG_FLAGS);
            InitWindow(
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                title
            );

            InitPhysics();
            SetPhysicsGravity(GRAVITY.x, GRAVITY.y);

            SetTargetFPS(60);

            gameMap.Init(
                SCREEN_WIDTH,
                SCREEN_HEIGHT
            );
            player.Init(
                (Vector2) {
                    gameMap.ground->position.x,
                    gameMap.ground->position.y,
                }
            );
        }

        Input checkUserInput() 
        {
            #ifdef CONSOLE_LOGGING_UPDATE
                std::cout << "Checking user input" << std::endl;     
            #endif // CONSOLE_LOGGING_UPDATE

            // Keyboard
            Input input = (Input) { false, false, false, false, false };

            input.left = IsKeyPressed(KEY_LEFT);
            input.right = IsKeyPressed(KEY_RIGHT);
            input.up = IsKeyPressed(KEY_UP);
            input.down = IsKeyPressed(KEY_DOWN);
            input.jump = IsKeyPressed(KEY_SPACE);

            #ifdef CONSOLE_LOGGING
                std::cout << "input.left = " << input.left << std::endl;
                std::cout << "input.right = " << input.right << std::endl;
                std::cout << "input.up = " << input.up << std::endl;
                std::cout << "input.down = " << input.down << std::endl;
                std::cout << "input.jump = " << input.jump << std::endl;
            #endif // CONSOLE_LOGGING

            return input;
        }


        void Draw()
        {
            #ifdef CONSOLE_LOGGING_UPDATE
                std::cout << "Drawing" << std::endl;     
            #endif // CONSOLE_LOGGING_UPDATE
            BeginDrawing();
                ClearBackground(BLACK);

                int bodiesCount = GetPhysicsBodiesCount();
                for (int i = 0; i < bodiesCount; i++)
                {
                    PhysicsBody body = GetPhysicsBody(i);
                    int vertices = GetPhysicsShapeVerticesCount(i);
                    for(int j = 0; j < vertices; j++)
                    {
                        Vector2 vertexA = GetPhysicsShapeVertex(body, j);
                        int k = (((j + 1) < vertices) ? (j + 1) : 0);
                        Vector2 vertexB = GetPhysicsShapeVertex(body, k);

                        DrawLineV(vertexA, vertexB, GREEN);
                    }
                }
            EndDrawing();
        }

        void Update()
        {
            #ifdef CONSOLE_LOGGING_UPDATE
                std::cout << "Updating" << std::endl;     
            #endif // CONSOLE_LOGGING_UPDATE

            UpdatePhysics();
            player.Move(checkUserInput());
        }

        void Close()
        {
            EndDrawing();
            ClosePhysics();
            CloseWindow();
        }

        Game()
        {
            std::cout << "Game object created" << std::endl;
            Init();
        }

        int getScreenWidth() { return SCREEN_WIDTH; }
        int getScreenHeight() { return SCREEN_HEIGHT; }
        Map getMap() { return gameMap; }
};


int main (int argc, char *argv[])
{
    Game game;

    // std::cout << "Started" << std::endl;
    while (!WindowShouldClose())
    {
        game.Update();
        game.Draw();
        if (IsKeyPressed(KEY_ESCAPE) || (IsKeyPressed(KEY_Q) && IsKeyPressed(KEY_LEFT_CONTROL)))
            game.Close();
    }

    return 0;
}
