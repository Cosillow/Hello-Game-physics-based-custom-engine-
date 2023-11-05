#pragma once

#include "2dphysics.hpp"
#include "animatedsprite.hpp"
#include "resourcemanager.hpp"

class Platform: public Body
{
public:
    Platform(Vector2 pos, int tileWidth): Body(pos, true)
    { this->addHitboxBB((tileWidth * Constants::TILE_SIZE) * Constants::SPRITE_SCALE, Constants::TILE_SIZE * Constants::SPRITE_SCALE); }
    Platform(): Platform(Vector2(), 1) {}

};