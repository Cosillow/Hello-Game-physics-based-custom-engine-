#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <cmath>
#include "renderwindow.hpp"
#include "2dphysics.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "sprite.hpp"
#include "platform.hpp"
#include "rope.hpp"

RenderWindow::RenderWindow(const std::string& title, int w, int h) :
_window(nullptr)
, _renderer(nullptr)
, _colorStack(std::stack<SDL_Color>())
, _camera(nullptr)
{
    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    if (!_window)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
        // Handle the error accordingly (e.g., throw an exception, clean up resources, etc.)
    }

    this->_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->_renderer)
    {
        std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
        // Handle the error accordingly (e.g., throw an exception, clean up resources, etc.)
    }
}



void RenderWindow::clear()
{
	SDL_RenderClear(this->_renderer);
}

void RenderWindow::display()
{
	SDL_RenderPresent(this->_renderer);
}

void RenderWindow::saveRenderingColor()
{
    SDL_Color currentColor;
    SDL_GetRenderDrawColor(this->_renderer, &currentColor.r, &currentColor.g, &currentColor.b, &currentColor.a);
    this->_colorStack.push(currentColor);
}

void RenderWindow::restoreRenderingColor()
{
    if (!this->_colorStack.empty())
    {
        SDL_Color previousColor = this->_colorStack.top();
        this->_colorStack.pop();
        SDL_SetRenderDrawColor(this->_renderer, previousColor.r, previousColor.g, previousColor.b, previousColor.a);
    }
}

void RenderWindow::render(const Player& player)
{
    if (!this->_camera)
    {
        std::cerr << "Camera not set for rendering!" << std::endl;
        return;
    }
    this->saveRenderingColor();
    this->render(player.getAnimatedSprite(), this->_camera->worldToScreen(player.getPosition()));
    if (Constants::debugMode && player.getHitbox())
        this->render(static_cast<Hitbox>(*(player.getHitbox())));
    this->restoreRenderingColor();
}

void RenderWindow::render(const Hitbox& hitbox)
{
    if (!this->_camera)
    {
        std::cerr << "Camera not set for rendering!" << std::endl;
        return;
    }
    this->saveRenderingColor();
    Hitbox::Type hitboxType = hitbox.getType();
    

    if (hitbox._inCollision)
        SDL_SetRenderDrawColor(this->_renderer, 255, 0, 0, 255); // Red
    else
        SDL_SetRenderDrawColor(this->_renderer, 0, 255, 0, 255); // Green

    if (hitboxType == Hitbox::Type::BoundingBox)
    {
        // Render bounding box
        
        const SDL_Rect& rect = this->_camera->worldToScreen(hitbox.getSDLRect());
        SDL_RenderDrawRect(this->_renderer, &rect);
    }
    else if (hitboxType == Hitbox::Type::Circle)
    {
        // Render circle
        const Vector2& center = this->_camera->worldToScreen(hitbox._center);
        float radius = hitbox._circleRadius;
        int centerX = static_cast<int>(center.x);
        int centerY = static_cast<int>(center.y);

        for (int x = centerX - radius; x <= centerX + radius; x++)
        {
            int yTop = centerY - static_cast<int>(sqrt(radius * radius - (x - centerX) * (x - centerX)));
            int yBottom = centerY + static_cast<int>(sqrt(radius * radius - (x - centerX) * (x - centerX)));

            SDL_RenderDrawLine(this->_renderer, x, yTop, x, yBottom);
        }
    }

    this->restoreRenderingColor();
}

void RenderWindow::render(const Platform& platform)
{
    this->saveRenderingColor();
    const Hitbox* hitbox = platform.getHitbox();

    if (!hitbox) {
        this->restoreRenderingColor();
        return;
    }
    
    this->render(static_cast<Hitbox>(*hitbox));

    this->restoreRenderingColor();
}

void RenderWindow::renderCamera()
{ 
    this->saveRenderingColor();
    if (Constants::debugMode)
    {
        // gray
        SDL_SetRenderDrawColor(this->_renderer, 150, 150, 150, 255);
        Vector2 centerScreen = this->_camera->worldToScreen(this->_camera->getCenter());

        int squareSize = 20;

        SDL_Rect squareRect = {
            static_cast<int>(centerScreen.x - squareSize / 2),
            static_cast<int>(centerScreen.y - squareSize / 2),
            squareSize,
            squareSize
        };
        // render camera focal point square
        SDL_RenderDrawRect(this->_renderer, &squareRect);
    }
    this->restoreRenderingColor();
}

void RenderWindow::render()
{
    if (!this->_camera)
        return;

    this->saveRenderingColor();

    // gray
    SDL_SetRenderDrawColor(this->_renderer, 150, 150, 150, 255);

    SDL_Rect worldRect = {
        0,
        0,
        static_cast<int>(Constants::GAME_WIDTH),
        static_cast<int>(Constants::GAME_HEIGHT)
    };
    SDL_Rect worldAdjustedScreen = this->_camera->worldToScreen(worldRect);
    SDL_RenderDrawRect(this->_renderer, &worldAdjustedScreen);
    
    this->restoreRenderingColor();
}

void RenderWindow::render(const Rope& rope)
{
    if (!this->_camera)
    {
        std::cerr << "Camera not set for rendering!" << std::endl;
        return;
    }

    this->saveRenderingColor();

    const auto& segments = rope.getSegments();
    
    size_t i;

    // brown
    SDL_SetRenderDrawColor(this->_renderer, 139, 69, 19, 255);
    for (i = 0; i < segments.size(); ++i)
    {
        const Vector2& pos = this->_camera->worldToScreen(segments[i]->getPosition());

        if (i > 0)
        {
            
            const Vector2& pos1 = this->_camera->worldToScreen(segments[i - 1]->getPosition());
            SDL_RenderDrawLine(this->_renderer, static_cast<int>(pos1.x), static_cast<int>(pos1.y),
                               static_cast<int>(pos.x), static_cast<int>(pos.y));
        }
    }
    // red
    SDL_SetRenderDrawColor(this->_renderer, 255, 0, 0, 255);
    for (i = 0; i < segments.size(); ++i)
    {
        const Vector2& pos = this->_camera->worldToScreen(segments[i]->getPosition());
        SDL_RenderDrawPoint(this->_renderer, static_cast<int>(pos.x), static_cast<int>(pos.y));
        if (Constants::debugMode && segments[i]->getHitbox())
            this->render(static_cast<Hitbox>(*(segments[i]->getHitbox())));
    }
    
    this->restoreRenderingColor();
}



// private methods
void RenderWindow::render(const Sprite& sprite, const Vector2 position)
{
    // does not take into account camera, just renders at position
    this->saveRenderingColor();

    SDL_Texture* spritesheet = sprite.getSpritesheet();
    if (!spritesheet) {
        this->restoreRenderingColor();
        return;
    }

    const SDL_Rect& spriteRect = sprite.getRect();

    SDL_Rect destRect;
    
    destRect.w = spriteRect.w * Constants::SPRITE_SCALE;
    destRect.h = spriteRect.h * Constants::SPRITE_SCALE;
    destRect.x = static_cast<int>(position.x - destRect.w / 2);
    destRect.y = static_cast<int>(position.y - destRect.h / 2);

    SDL_RendererFlip flip = sprite.getMirrorX() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(this->_renderer, spritesheet, &spriteRect, &destRect, 0.0, nullptr, flip);

    this->restoreRenderingColor();
}

void RenderWindow::cleanUp()
{
    if (this->_renderer) {
        SDL_DestroyRenderer(this->_renderer);
        this->_renderer = nullptr;
    }
    if (_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
}

// void RenderWindow::render(const Canvas& canvas) {
//     this->saveRenderingColor();

//     // Render the checkered background
//     int gridSize = 50;  // Size of each grid box
//     int numColumns = std::ceil(static_cast<float>(Constants::WINDOW_WIDTH) / gridSize);
//     int numRows = std::ceil(static_cast<float>(Constants::WINDOW_HEIGHT) / gridSize);

//     for (int row = 0; row < numRows; ++row) {
//         for (int col = 0; col < numColumns; ++col) {
//             SDL_Rect gridRect;
//             gridRect.x = col * gridSize;
//             gridRect.y = row * gridSize;
//             gridRect.w = gridSize;
//             gridRect.h = gridSize;

//             if ((row + col) % 2 == 0) {
//                 // White box
//                 SDL_SetRenderDrawColor(this->_renderer, 255, 255, 255, 255);
//             } else {
//                 // Grey box
//                 SDL_SetRenderDrawColor(this->_renderer, 200, 200, 200, 255);
//             }

//             SDL_RenderFillRect(this->_renderer, &gridRect);
//         }
//     }

//     // Render the sprite sheet
//     SDL_Texture* spriteSheet = canvas.getPhoto();
//     if (!spriteSheet) {
//         this->restoreRenderingColor();
//         return;
//     }

//     const SDL_Rect& box = canvas.getBox();

//     // Calculate the zoom factor based on the current zoom percentage
//     float zoomFactor = canvas.getZoom() / 100.0f;

//     SDL_Rect destRect;
//     destRect.w = static_cast<int>(box.w * zoomFactor);
//     destRect.h = static_cast<int>(box.h * zoomFactor);
//     destRect.x = static_cast<int>(box.x);
//     destRect.y = static_cast<int>(box.y);

//     SDL_RenderCopy(this->_renderer, spriteSheet, nullptr, &destRect);

//     // Render the selection box
//     const SDL_Rect& selectionBox = canvas.getSelection();
    
//     if (selectionBox.w && selectionBox.h) {
//         // only draw a box if it isn't empty
//         SDL_Rect selectionRect;
//         selectionRect.x = static_cast<int>(selectionBox.x * zoomFactor);
//         selectionRect.y = static_cast<int>(selectionBox.y * zoomFactor);
//         selectionRect.w = static_cast<int>(selectionBox.w);
//         selectionRect.h = static_cast<int>(selectionBox.h);
//         SDL_SetRenderDrawColor(this->_renderer, 255, 0, 0, 255);  // Red color for the selection box outline
//         SDL_RenderDrawRect(this->_renderer, &selectionRect);
//     }


//     this->restoreRenderingColor();
// }

