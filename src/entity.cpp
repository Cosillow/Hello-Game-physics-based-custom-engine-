#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <vector>
#include "entity.hpp"
#include "constants.hpp"

Entity::Entity(SDL_FPoint pos, Texture& tex):
    _position(pos),
    _tex(tex),
    _acceleration({0,0}),
    _velocity({0,0}),
    _mass(20.0f),
    _size({0,0})
{
    int roundedWidth = 0;
    int roundedHeight = 0;
    SDL_QueryTexture(_tex.get(), nullptr, nullptr, &roundedWidth, &roundedHeight);
    _size.x = static_cast<float>(roundedWidth);
    _size.y = static_cast<float>(roundedHeight);
}

const SDL_Rect Entity::getBoundingBox() const
{
    SDL_Rect boundingBox;
    boundingBox.x = static_cast<int>(_position.x);
    boundingBox.y = static_cast<int>(_position.y);
    boundingBox.w = _size.x;
    boundingBox.h = _size.y;
    return boundingBox;
}


void Entity::update(float deltaTime)
{       
    _velocity.x += _acceleration.x * deltaTime;
    _velocity.y += _acceleration.y * deltaTime;
    _position.x += _velocity.x * deltaTime;
    _position.y += _velocity.y * deltaTime;
}

void Entity::applyForce(const SDL_FPoint& force)
{
    _acceleration.x += force.x / _mass;
    _acceleration.y += force.y / _mass;
}

void Entity::applyImpulse(const SDL_FPoint& impulse) {
    _velocity.x += impulse.x / _mass;
    _velocity.y += impulse.y / _mass;
}

void Entity::applyGravity() {
    SDL_FPoint gravityForce = {0.0f, Constants::GRAVITY * _mass};
    applyForce(gravityForce);
}
