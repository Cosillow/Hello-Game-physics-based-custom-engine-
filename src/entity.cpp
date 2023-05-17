#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"

Entity::Entity(Vector2f pos, Texture& tex)
: _pos(pos), _tex(tex)
{
    SDL_QueryTexture(_tex.get(), NULL, NULL, &_currentFrame.w, &_currentFrame.h);
    _currentFrame.x = 0;
    _currentFrame.y = 0;
}

