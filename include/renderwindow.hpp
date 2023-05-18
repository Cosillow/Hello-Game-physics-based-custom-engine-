#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#include "entity.hpp"

class RenderWindow 
{
public:
	RenderWindow(const std::string& title, int w, int h);
	~RenderWindow() { cleanUp(); }
	SDL_Renderer* getRenderer() const { return _renderer; }
	void render(Entity& entity);
	void display();
	void clear();
private:
	void cleanUp();
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};
