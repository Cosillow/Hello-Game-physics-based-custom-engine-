#include "inputmanager.hpp"

InputManager::InputManager()
{
    keyState = SDL_GetKeyboardState(&keyLength);
}

InputManager::~InputManager()
{
}

void InputManager::update()
{
    SDL_PumpEvents();  // update SDL event state
}

bool InputManager::isKeyDown(SDL_Scancode key)
{
    return keyState[key] == 1;
}

bool InputManager::isKeyUp(SDL_Scancode key)
{
    return keyState[key] == 0;
}
