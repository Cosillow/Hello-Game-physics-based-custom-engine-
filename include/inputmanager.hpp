#pragma once

#include <SDL2/SDL.h>

class Game;

class InputManager
{
public:
    InputManager();
    void update(Game& game);
    bool isKeyDown(SDL_Scancode key);
    bool isKeyUp(SDL_Scancode key);
    bool isMouseButtonDown(Uint8 button);
    bool isMouseButtonUp(Uint8 button);
    int getMouseX();
    int getMouseY();

private:
    const Uint8* _keyState;
    int _keyLength;
    int _mouseX;
    int _mouseY;
    Uint32 _mouseState;
};
