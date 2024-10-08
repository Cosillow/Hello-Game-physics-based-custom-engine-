#pragma once

#include <SDL2/SDL.h>
#include "2dphysics.hpp"

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
    Vector2 getMousePosition() const { return this->_mousePosition; }
    Vector2 getPreviousMousePosition() const { return this->_previousMousePosition; }
    int getMouseScrollDelta() const { return this->_mouseScrollDelta; }

private:
    const Uint8* _keyState;
    int _keyLength;
    Vector2 _mousePosition;
    Vector2 _previousMousePosition;
    Uint32 _mouseState;
    int _mouseScrollDelta;
};
