#pragma once
#include "2dphysics.hpp"

namespace Constants {
    const float PLAYER_SPEED = 20;
    const Vector2 GRAVITY = {0.0, 40000}; 
    const float PLAYER_JUMP = 60000;
    const float DAMPING = 0.95;
    const float RESTING_ROPE_LENGTH = 1.0;
    const float GRAPPLING_HOOK_SPEED = 1000;
    const float WINDOW_HEIGHT = 720;
    const float WINDOW_WIDTH = 1280;
    const float PLAYER_MASS = 200;
    const float ROPE_MASS = 10;
}
