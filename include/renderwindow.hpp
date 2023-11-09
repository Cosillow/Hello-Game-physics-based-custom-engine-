#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <stack>
#include <memory>

#include "camera.hpp"
#include "2dphysics.hpp"

class Player;
class SpriteContainer;
class Sprite;
class Hitbox;
class Platform;
class Rope;

class RenderWindow 
{
public:
	RenderWindow(const std::string& title, int w, int h);
	~RenderWindow() { cleanUp(); }
	

	// method overrides: render()
	void render();
	void render(const Player& player);
	void render(const Hitbox& hitbox);
	void render(const Platform& platform);
	void render(const Rope& rope);
	void renderCamera();

	// getters
	SDL_Renderer& getRenderer() const { return *(this->_renderer); }
	SDL_Window& getWindow() const { return *(this->_window); }
	void saveRenderingColor();
    void restoreRenderingColor();

	void addCamera(std::shared_ptr<Camera> cam) { this->_camera = cam; }
	void setFullscreen(const bool on) { SDL_SetWindowFullscreen(this->_window, on ? SDL_WINDOW_FULLSCREEN : 0); }
	void display();
	void clear();
private:
	void cleanUp();
	void render(const Sprite& sprite, const Vector2 position);
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::stack<SDL_Color> _colorStack;
	std::shared_ptr<Camera> _camera;
};
