#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "2dphysics.hpp"
#include "player.hpp"

class Circle;
class Rectangle;
class Triangle;
class Platform;

class CollisionManager
{
public:
    void resolveBounds(Player& player) const;
    void resolveBounds(Player& player, Platform& platform) const;
};
