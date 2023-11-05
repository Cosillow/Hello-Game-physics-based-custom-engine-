#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <stack>

#include "2dphysics.hpp"

class Player;
class SpriteContainer;
class Sprite;
class Hitbox;
class Platform;

class RenderWindow 
{
public:
	RenderWindow(const std::string& title, int w, int h);
	~RenderWindow() { cleanUp(); }
	

	// method overrides: render()
	void render(const Body& Body);
	void render(const Player& player);
	void render(const Sprite& sprite, const Vector2 position);
	void render(const Hitbox& hitbox);
	void render(const Platform& platform);

	// getters
	SDL_Renderer& getRenderer() const { return *(this->_renderer); }
	SDL_Window& getWindow() const { return *(this->_window); }
	void saveRenderingColor();
    void restoreRenderingColor();

	void setFullscreen(const bool on) { SDL_SetWindowFullscreen(this->_window, on ? SDL_WINDOW_FULLSCREEN : 0); }
	void display();
	void clear();
private:
	void cleanUp();
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::stack<SDL_Color> _colorStack;
};
