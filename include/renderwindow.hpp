#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <stack>

#include "2dphysics.hpp"

class Rope;
class Player;
class GrapplingHook;
class Item;

class RenderWindow 
{
public:
	RenderWindow(const std::string& title, int w, int h);
	~RenderWindow() { cleanUp(); }
	SDL_Renderer* getRenderer() const { return _renderer; }

	// method overrides: render()
	void render(Body& Body);
	void render(Player& player);
	void render(Item& item);
	void render(GrapplingHook& player);
	void render(Rope& rope);

	void saveRenderingColor();
    void restoreRenderingColor();

	void display();
	void clear();
private:
	void cleanUp();
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::stack<SDL_Color> _colorStack;
};
