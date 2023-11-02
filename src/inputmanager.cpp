#include "inputmanager.hpp"
#include "game.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

InputManager::InputManager()
{
    _keyState = SDL_GetKeyboardState(&_keyLength),
    _mousePosition = {0,0};
    _mouseState = 0;
}

void InputManager::update(Game& game)
{
    SDL_Event e;
    int x;
    int y;
    _mouseState = SDL_GetMouseState(&x, &y); // Update mouse state and position
    _previousMousePosition = _mousePosition;
    _mousePosition = { static_cast<float>(x), static_cast<float>(y) };
    _mouseScrollDelta = 0;
    while (SDL_PollEvent(&e))
    {
        ImGui_ImplSDL2_ProcessEvent(&e);

        switch (e.type)
        {
            case SDL_QUIT:
                game.quit();
                break;

            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    // Handle window resize event
                    // int newWidth = e.window.data1;
                    // int newHeight = e.window.data2;
                }
                break;
            case SDL_MOUSEWHEEL:
                this->_mouseScrollDelta = e.wheel.y;
                break;
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
