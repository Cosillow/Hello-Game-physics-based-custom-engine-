#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string.h>

#include "renderwindow.hpp"
#include "entity.hpp"
#include "texture.hpp"


RenderWindow::RenderWindow(const std::string& title, int w, int h)
    : _window(nullptr), _renderer(nullptr)
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
	SDL_Rect src; 
	src.x = 0;
	src.y = 0;
	src.w = entity.getBoundingBox().w;
	src.h = entity.getBoundingBox().h;

	SDL_Rect dst;
	dst.x = entity.getPosition().x;
	dst.y = entity.getPosition().y;
	dst.w = entity.getBoundingBox().w;
	dst.h = entity.getBoundingBox().h;

	SDL_RenderCopy(_renderer, entity.getTexture().get(), &src, &dst);
}

void RenderWindow::display()
{
	SDL_RenderPresent(_renderer);
}