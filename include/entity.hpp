#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <math.hpp>

class Entity
{
public:
	Entity(Vector2f pos, SDL_Texture* tex);
	Vector2f& getPos() { return _pos; }
	SDL_Texture* getTex() { return _tex; }
	SDL_Rect getCurrentFrame() { return _currentFrame; }
private:
	Vector2f _pos;
	SDL_Rect _currentFrame;
	SDL_Texture* _tex;
};