#include <cstdlib> // for rng 
#include <iostream> // for console logging
#include <raylib.h> // for graphical rendering

#define PHYSAC_IMPLEMENTATION
#include "physac.h" // for physics
#include "helpers.h" // for various helper functions

#define CONSOLE_LOGGING // logs info to console
#define TESTING_PLATFORMS // generates platforms on the sides for physics testing
// #define CONSOLE_LOGGING_UPDATE // logs info on every update call (very messy)

#define MAX_PLATFORMS 5
#define PLATFORM_WIDTH 100
#define PLATFORM_HEIGHT 20
#define PHYSICS_ENABLED false
const Vector2 MAX_VELOCITY = (Vector2) { 1.15f, 4.0f };
const Vector2 ACCELERATION = (Vector2) { 1.0f, 2.0f };
const Vector2 GRAVITY = (Vector2) { 0.0f, 9.81f };

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
    bool refresh;
} Input;
// For clarity
typedef PhysicsBody Platform;
// Stores all of the platforms and their locations
class Map
{
    private:
        #ifdef TESTING_PLATFORMS
            Platform platforms[MAX_PLATFORMS + 2];
        #else
            Platform platforms[MAX_PLATFORMS];
        #endif // TESTING_PLATFORMS
        const int PLATFORM_OFFSET = 20;

        void GeneratePlatforms(int screenWidth, int screenHeight)
        {
            #ifdef CONSOLE_LOGGING
                std::cout << "Generating platforms" << std::endl;     
            #endif // CONSOLE_LOGGING

            // This is something you should think about?
                // Why did I go through all this hassle instead of using a foreach loop
            for (int sectionWidth = (screenWidth/MAX_PLATFORMS), i = 0; i < MAX_PLATFORMS; i++)
            {
                int minX = sectionWidth * i;
                int maxX = sectionWidth * (i + 1);
                int minY = 0.15f*screenHeight;
                int maxY = 0.85f*(screenHeight);
                        
                Vector2 position = (Vector2) {
                        clamp_f(std::rand() % maxX, minX, maxX),
                        clamp_f(std::rand() % maxY, minY, maxY)
                    };

                platforms[i] = CreatePhysicsBodyRectangle(
                            position,
                            PLATFORM_WIDTH, PLATFORM_HEIGHT,
                            1
                );

                platforms[i]->isGrounded = false;
                platforms[i]->useGravity = false;
                platforms[i]->enabled = PHYSICS_ENABLED;
            }
            #ifdef TESTING_PLATFORMS
                platforms[MAX_PLATFORMS] = CreatePhysicsBodyRectangle(
                    (Vector2) { 0, screenHeight - (float)PLATFORM_OFFSET},
                    50, screenHeight,
                    1
                );
                platforms[MAX_PLATFORMS]->isGrounded = false;
                platforms[MAX_PLATFORMS]->useGravity = false;
                platforms[MAX_PLATFORMS]->enabled = PHYSICS_ENABLED;

                platforms[MAX_PLATFORMS + 1] = CreatePhysicsBodyRectangle(
                    (Vector2) { screenWidth - (float)PLATFORM_OFFSET, screenHeight - (float)PLATFORM_OFFSET},
                    50, screenHeight,
                    1
                );
                platforms[MAX_PLATFORMS + 1]->isGrounded = false;
                platforms[MAX_PLATFORMS + 1]->useGravity = false;
                platforms[MAX_PLATFORMS + 1]->enabled = PHYSICS_ENABLED;
            #endif // TESTING_PLATFORMS
        }

        Platform GenerateGround(int screenWidth, int screenHeight)
        {
            #ifdef CONSOLE_LOGGING
                std::cout << "Generating ground" << std::endl;     
            #endif // CONSOLE_LOGGING

            Vector2 position = (Vector2) {
                (float)screenWidth / 2,
                screenHeight - (float)PLATFORM_OFFSET 
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

            Vector2 position = (Vector2) {
                groundPosition.x / 2.0f,
                groundPosition.y - 10,
            };

            body = CreatePhysicsBodyRectangle(
                position,   
                50, 50,
                1.0f
            );

            body->isGrounded = true;
            body->useGravity = true;
            body->freezeOrient = true;
            body->dynamicFriction = 5;
        }

        void Jump()
        {
            if (body->isGrounded == false) {
                #ifdef CONSOLE_LOGGING
                    std::cout << "Player in air. Not jumping" << std::endl;
                #endif // CONSOLE_LOGGING
                return;
            }

            #ifdef CONSOLE_LOGGING
                std::cout << "Jumping" << std::endl;     
            #endif // CONSOLE_LOGGING

            body->velocity.y -= ACCELERATION.y;
            body->isGrounded = false;
        }

        void Move(Input input)
        {
            #ifdef CONSOLE_LOGGING_UPDATE
                std::cout << "Moving" << std::endl;     
            #endif // CONSOLE_LOGGING

            if (input.left)
            {
                // body->velocity.x -= ACCELERATION.x;
                std::cout << "Input left" << std::endl;
                body->velocity.x = clamp(body->velocity.x - ACCELERATION.x, (-1 * MAX_VELOCITY.x), 0);
            }
            if (input.right)
            {
                // body->velocity.x += ACCELERATION.x;
                body->velocity.x = clamp(body->velocity.x + ACCELERATION.x, 0, MAX_VELOCITY.x);
            }
            if (input.down)
            {
                // TODO Implement a function similar to Smash's fast fall system
                if (body->isGrounded == false) 
                {
                    body->velocity.y += ACCELERATION.y;
                }
            }
            if (input.up)
                Jump();
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

        void Refresh()
        {
            Close();            
            InitPhysics();
            SetPhysicsGravity(GRAVITY.x, GRAVITY.y);
            gameMap.Init(SCREEN_WIDTH, SCREEN_HEIGHT);
            player.Init(
                    (Vector2) {
                        gameMap.ground->position.x,
                        gameMap.ground->position.y
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

            input.left = IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT);
            input.right = IsKeyPressed(KEY_RIGHT)|| IsKeyDown(KEY_RIGHT);
            input.up = IsKeyPressed(KEY_UP);
            input.down = IsKeyPressed(KEY_DOWN);
            input.jump = IsKeyPressed(KEY_SPACE);
            input.refresh = IsKeyPressed(KEY_R);

            #ifdef CONSOLE_LOGGING_UPDATE
                std::cout << "input.left = " << input.left << std::endl;
                std::cout << "input.right = " << input.right << std::endl;
                std::cout << "input.up = " << input.up << std::endl;
                std::cout << "input.down = " << input.down << std::endl;
                std::cout << "input.jump = " << input.jump << std::endl;
                std::cout << "input.refresh = " << input.refresh << std::endl;
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
                        int k = (((j + 1) < vertices) ? (j + 1) : 0); // If we're at the last vertex, we need to draw a line to 0
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
        {
            game.Close();
            CloseWindow();
        }
    }

    return 0;
}
