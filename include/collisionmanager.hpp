#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "entity.hpp"
#include "player.hpp"

class CollisionManager
{
public:
    // bool checkAndResolve(Entity& entity1, Entity& entity2) const;
    bool resolveBounds(Player& player) const;
};
