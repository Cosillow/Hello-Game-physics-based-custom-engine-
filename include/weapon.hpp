#pragma once

#include "entity.hpp"

class Weapon : public Entity
{
public:
    Weapon(SDL_FPoint pos, Texture& tex): Entity(pos, tex) {};
    virtual void attack() = 0;
    virtual void block() = 0;
    virtual void update(float deltaTime) override {};

protected:
    bool _attacking;
    bool _blocking;
};
