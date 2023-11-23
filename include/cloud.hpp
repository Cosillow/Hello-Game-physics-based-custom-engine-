#pragma once

#include "2dphysics.hpp"

class Cloud: public Body
{
public:
    Cloud(Vector2 pos) :
    Body(pos, true)
    , _touched(false)
    { this->addHitboxBB(10 * Constants::SPRITE_SCALE, Constants::TILE_SIZE * Constants::SPRITE_SCALE); }
    Cloud(): Cloud(Vector2()) { }

    void touchCloud() { this->_touched = true; }

    bool getTouched() {  }

    void update(float deltaTime) override;

private:
    bool _touched;
};
