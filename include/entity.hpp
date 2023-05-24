#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <memory>
#include <unordered_map>
#include "texture.hpp"

class Entity
{
public:
    enum class ForceType
    {
        Gravity,
        Jump
    };

    Entity(SDL_FPoint pos, Texture& tex);
    const SDL_FPoint& getPosition() const { return _position; }
    const Texture& getTexture() const { return _tex; }
    float getMass() const { return _mass; }
    SDL_FPoint getVelocity() const { return _velocity; }
    void addForce(ForceType forceType);
    void removeForce(ForceType forceType);
    void applyImpulse(const SDL_FPoint& impulse);
    virtual void setPosition(const SDL_FPoint& pos) { _position = pos; }
    void setVelocity(const SDL_FPoint& vel) { _velocity = vel; }
    void setAcceleration(const SDL_FPoint& acc) { _acceleration = acc; }

    const SDL_Rect getBoundingBox() const;
    virtual void update(float deltaTime);
private:
    using ForcesMap = std::unordered_map<ForceType, SDL_FPoint>;
    ForcesMap _forces;
    SDL_FPoint _position;
	Texture& _tex;
    SDL_FPoint _acceleration;
    SDL_FPoint _velocity;
    float _mass;
    SDL_FPoint _size;
};
