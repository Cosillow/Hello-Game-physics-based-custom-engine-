#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include "renderwindow.hpp"
#include "entity.hpp"
#include "texture.hpp"
#include "player.hpp"
#include "grapplinghook.hpp"
#include "constants.hpp"
#include "rope.hpp"
#include "item.hpp"

RenderWindow::RenderWindow(const std::string& title, int w, int h)
    : _window(nullptr), _renderer(nullptr), _colorStack(std::stack<SDL_Color>())
{
    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    if (!_window)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
        // Handle the error accordingly (e.g., throw an exception, clean up resources, etc.)
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer)
    {
        std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
        // Handle the error accordingly (e.g., throw an exception, clean up resources, etc.)
    }
}


void RenderWindow::cleanUp()
{
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    if (_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
}


void RenderWindow::clear()
{
	SDL_RenderClear(_renderer);
}

void RenderWindow::render(Entity& entity)
{
    this->saveRenderingColor();

    // Set the rendering color to grey
    SDL_SetRenderDrawColor(_renderer, 128, 128, 128, 255);

    // Create a rectangle with a size of 200x50
    SDL_Rect rect;
    rect.x = static_cast<int>(entity.getPosition().x);
    rect.y = static_cast<int>(entity.getPosition().y);
    rect.w = 200;
    rect.h = 50;

    // Render the rectangle
    SDL_RenderFillRect(_renderer, &rect);

    this->restoreRenderingColor();
}


void RenderWindow::render(Player& player)
{
    this->saveRenderingColor();
    this->render(static_cast<Entity&>(player));
    Item* equippedItem = player.getEquippedItem();
    if (equippedItem)
    {
        this->render(*equippedItem);
    }
    // TODO render player sprite
    

    this->restoreRenderingColor();
}

void RenderWindow::render(Item& item)
{
    item.renderItem(*this);
}

void RenderWindow::render(GrapplingHook& grapplingHook)
{
    this->saveRenderingColor();

    const Player& player = grapplingHook.getPlayer();

    if (grapplingHook.getState() == GrapplingHook::State::Idle) {
        Vector2 center = player.getBoundingBoxCenter();

        // Calculate the line endpoints based on the look angle
        double angleRadians = player.getLookAngle() * M_PI / 180.0;
        int lineLength = 1000;
        int lineX = static_cast<int>(center.x + lineLength * cos(angleRadians));
        int lineY = static_cast<int>(center.y + lineLength * sin(angleRadians));

        // Draw a bright green line
        SDL_SetRenderDrawColor(_renderer, 0, 255, 0, 255);
        SDL_RenderDrawLine(_renderer, static_cast<int>(center.x), static_cast<int>(center.y), lineX, lineY);
    } else if (grapplingHook.getState() == GrapplingHook::State::Extending) {

        this->render(static_cast<Entity&>(grapplingHook));

        // Set the rendering color to red
        SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);

        // Render the grappling hook as a square
        Vector2 hookPosition = grapplingHook.getPosition();
        int hookSize = 50;
        SDL_Rect hookRect;
        hookRect.x = static_cast<int>(hookPosition.x - hookSize / 2);
        hookRect.y = static_cast<int>(hookPosition.y - hookSize / 2);
        hookRect.w = hookSize;
        hookRect.h = hookSize;
        SDL_RenderFillRect(_renderer, &hookRect);
    }

    if (grapplingHook.getState() != GrapplingHook::State::Idle) this->render(grapplingHook.getRope());    

    this->restoreRenderingColor();
}



void RenderWindow::render(Rope& rope)
{
    this->saveRenderingColor();
    const std::vector<Entity>& links = rope.getLinks();

    // Set the rendering color to brown
    SDL_SetRenderDrawColor(_renderer, 139, 69, 19, 255);

    // Render each link of the rope as a line
    for (int i = 0; i < rope.getNumLinks() - 1; ++i)
    {
        const Entity& currentLink = links[i];
        const Entity& nextLink = links[i + 1];

        // Render the line between the current link and the next link
        SDL_RenderDrawLine(_renderer, static_cast<int>(currentLink.getPosition().x), static_cast<int>(currentLink.getPosition().y),
                           static_cast<int>(nextLink.getPosition().x), static_cast<int>(nextLink.getPosition().y));
    }

    // Render the last link to the end anchor point
    const Entity& lastLink = links.back();
    SDL_RenderDrawLine(_renderer, static_cast<int>(lastLink.getPosition().x), static_cast<int>(lastLink.getPosition().y),
                       static_cast<int>(rope.getEndAnchor().x), static_cast<int>(rope.getEndAnchor().y));

    this->restoreRenderingColor();
}





void RenderWindow::display()
{
	SDL_RenderPresent(_renderer);
}

void RenderWindow::saveRenderingColor()
    {
        SDL_Color currentColor;
        SDL_GetRenderDrawColor(_renderer, &currentColor.r, &currentColor.g, &currentColor.b, &currentColor.a);
        _colorStack.push(currentColor);
    }

void RenderWindow::restoreRenderingColor()
{
    if (!_colorStack.empty())
    {
        SDL_Color previousColor = _colorStack.top();
        _colorStack.pop();
        SDL_SetRenderDrawColor(_renderer, previousColor.r, previousColor.g, previousColor.b, previousColor.a);
    }
}