#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <vector>
#include "entity.hpp"

Entity::Entity(SDL_FPoint pos, Texture& tex):
_position(pos),
_currentFrame({0,0,0,0}),
_tex(tex),
_acceleration({0,0}),
_velocity({0,0})
{
    SDL_QueryTexture(_tex.get(), NULL, NULL, &_currentFrame.w, &_currentFrame.h);
    _currentFrame.x = 0;
    _currentFrame.y = 0;
}

void Entity::update(float deltaTime) {       
        _velocity.x += _acceleration.x * deltaTime;
        _velocity.y += _acceleration.y * deltaTime;
        _position.x += _velocity.x * deltaTime;
        _position.y += _velocity.y * deltaTime;
    }




void Entity::applyForce(const SDL_FPoint& force) {
    _acceleration.x += force.x / _mass;
    _acceleration.y += force.y / _mass;
}

void Entity::applyImpulse(const SDL_FPoint& impulse) {
    _velocity.x += impulse.x / _mass;
    _velocity.y += impulse.y / _mass;
}
