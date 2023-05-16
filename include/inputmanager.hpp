#pragma once

#include <SDL2/SDL.h>

class InputManager
{
public:
    InputManager();
    ~InputManager();
    void update();
    bool isKeyDown(SDL_Scancode key);
    bool isKeyUp(SDL_Scancode key);
private:
    const Uint8* keyState;
    int keyLength;
};
