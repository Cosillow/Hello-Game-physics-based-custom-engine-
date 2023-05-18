#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "entity.hpp"

class CollisionManager
{
public:
    static bool checkCollision(const Entity& entity1, const Entity& entity2);
};
