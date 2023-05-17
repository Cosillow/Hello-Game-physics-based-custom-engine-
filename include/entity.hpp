#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <math.hpp>

#include "texture.hpp"

class Entity
{
public:
    Entity(Vector2f pos, Texture& tex);
    Vector2f& getPos() { return _pos; }
    Texture& getTex() { return _tex; }
    SDL_Rect getCurrentFrame() { return _currentFrame; }
private:
    Vector2f _pos;
    SDL_Rect _currentFrame;
	Texture& _tex;
};
