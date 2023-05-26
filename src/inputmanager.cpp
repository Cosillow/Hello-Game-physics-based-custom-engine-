#include "inputmanager.hpp"
#include "game.hpp"

InputManager::InputManager()
{
    _keyState = SDL_GetKeyboardState(&_keyLength);
    _mouseX = 0;
    _mouseY = 0;
    _mouseState = 0;
}

void InputManager::update(Game& game)
{
    SDL_Event event;
    _mouseState = SDL_GetMouseState(&_mouseX, &_mouseY); // Update mouse state and position

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            game.quit();
        }
        // else if (event.type == SDL_MOUSEMOTION)
        // {
        //     _mouseX = event.motion.x;
        //     _mouseY = event.motion.y;
        // }
    }
}


bool InputManager::isKeyDown(SDL_Scancode key)
{
    return _keyState[key] == 1;
}

bool InputManager::isKeyUp(SDL_Scancode key)
{
    return _keyState[key] == 0;
}

bool InputManager::isMouseButtonDown(Uint8 button)
{
    return (_mouseState & SDL_BUTTON(button)) != 0;
}

bool InputManager::isMouseButtonUp(Uint8 button)
{
    return (_mouseState & SDL_BUTTON(button)) == 0;
}

int InputManager::getMouseX()
{
    return _mouseX;
}

int InputManager::getMouseY()
{
    return _mouseY;
}
