#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <vector>
#include <algorithm>
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
    boundingBox.w = static_cast<int>(_size.x);
    boundingBox.h = static_cast<int>(_size.y);
    return boundingBox;
}

void Entity::update(float deltaTime)
{       
    // Apply accumulated forces
    for (const auto& forcePair : _forces) {
        const SDL_FPoint& force = forcePair.second;
        _acceleration.x += force.x / _mass;
        _acceleration.y += force.y / _mass;
    }
    // _forces.clear();

    _velocity.x += _acceleration.x * deltaTime;
    _velocity.y += _acceleration.y * deltaTime;
    _position.x += _velocity.x * deltaTime;
    _position.y += _velocity.y * deltaTime;

}

void Entity::addForce(ForceType forceType)
{
    switch (forceType)
    {
        case ForceType::Gravity:
            _forces[forceType] = { 0.0f, Constants::GRAVITY };
            break;
        case ForceType::Jump:
            _forces[forceType] = { 0.0f, -Constants::PLAYER_SPEED };
            break;
        default:
            break;
    }
}


void Entity::removeForce(ForceType forceType)
{
    this->_forces.erase(forceType);
}


void Entity::applyImpulse(const SDL_FPoint& impulse)
{
    this->_velocity.x += impulse.x / this->_mass;
    this->_velocity.y += impulse.y / this->_mass;
}