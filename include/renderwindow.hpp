#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

#include "entity.hpp"

class RenderWindow 
{
public:
	RenderWindow(const std::string& p_title, int p_w, int p_h);
	~RenderWindow() { cleanUp(); }
	SDL_Renderer* getRenderer() const { return renderer; }
	void render(Entity& p_entity);
	void display();
	void clear();
private:
	void cleanUp();
	SDL_Window* window;
	SDL_Renderer* renderer;
};