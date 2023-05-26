#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <vector>
#include <algorithm>
#include "entity.hpp"
#include "constants.hpp"

Entity::Entity(Vector2 pos):
    _position(pos),
    _acceleration({0,0}),
    _velocity({0,0}),
    _mass(20.0f),
    _size({200, 50}) {}

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
        const Vector2& force = forcePair.second;
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


void Entity::applyImpulse(const Vector2& impulse)
{
    this->_velocity.x += impulse.x / this->_mass;
    this->_velocity.y += impulse.y / this->_mass;
}

Vector2 Entity::getBoundingBoxCenter() const
{
    const SDL_Rect& boundingBox = getBoundingBox();
    float centerX = static_cast<float>(boundingBox.x + boundingBox.w / 2);
    float centerY = static_cast<float>(boundingBox.y + boundingBox.h / 2);
    return { centerX, centerY };
}
