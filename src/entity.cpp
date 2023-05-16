#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"

Entity::Entity(Vector2f pos, SDL_Texture* tex)
:_pos(pos), _tex(tex)
{
	_currentFrame.x = 0;
	_currentFrame.y = 0;
	_currentFrame.w = 32;
	_currentFrame.h = 32;
}
