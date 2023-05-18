#include "inputmanager.hpp"

InputManager::InputManager()
{
    _keyState = SDL_GetKeyboardState(&_keyLength);
}

void InputManager::update()
{
    SDL_PumpEvents();  // update SDL event state
}

bool InputManager::isKeyDown(SDL_Scancode key)
{
    return _keyState[key] == 1;
}

bool InputManager::isKeyUp(SDL_Scancode key)
{
    return _keyState[key] == 0;
}
