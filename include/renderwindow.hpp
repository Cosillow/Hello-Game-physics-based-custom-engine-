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
class SpriteContainer;
class Sprite;
class Hitbox;
class Canvas;

class RenderWindow 
{
public:
	RenderWindow(const std::string& title, int w, int h);
	~RenderWindow() { cleanUp(); }
	SDL_Renderer& getRenderer() const { return *(this->_renderer); }

	// method overrides: render()
	void render(const Body& Body);
	void render(const Player& player);
	void render(const Item& item);
	void render(const GrapplingHook& player);
	void render(const Rope& rope);
	void render(const Sprite& sprite, const Vector2 position);
	void render(const Hitbox& hitbox);
	void render(const Canvas& canvas);

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
