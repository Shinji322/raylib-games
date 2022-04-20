#pragma once
#ifndef INPUT_H
#define INPUT_H
#include <raylib.h>

typedef struct Input 
{
    bool left;
    bool right;
    bool up;
    bool down;
} Input;

class InputManager
{
public:
        Input checkUserInput()
        {
            Input input = (Input) {false, false, false, false};

            input.left = IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT);
            input.right = IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT);
            input.up = IsKeyPressed(KEY_UP);
            input.down = IsKeyPressed(KEY_DOWN);

            return input;
        }
};


#endif // !INPUT_H
