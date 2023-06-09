#include "inputmanager.hpp"
#include "game.hpp"

InputManager::InputManager()
{
    _keyState = SDL_GetKeyboardState(&_keyLength),
    _mousePosition = {0,0};
    _mouseState = 0;
}

void InputManager::update(Game& game)
{
    SDL_Event event;
    int x;
    int y;
    _mouseState = SDL_GetMouseState(&x, &y); // Update mouse state and position
    _previousMousePosition = _mousePosition;
    _mousePosition = { static_cast<float>(x), static_cast<float>(y) };
    _mouseScrollDelta = 0;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            game.quit();
        }
        else if (event.type == SDL_MOUSEWHEEL)
        {
            this->_mouseScrollDelta = event.wheel.y;
        }
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
