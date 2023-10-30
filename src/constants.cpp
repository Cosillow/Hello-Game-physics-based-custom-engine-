#include "constants.hpp"

namespace Constants {
    bool debugMode = false;
    float PLAYER_SPEED = 1230.0;
    float PLAYER_MAX_SPEED = 10.0;
    float PLAYER_FRICTION = 1026.0;
    float GRAVITY = 1600.0; 
    float PLAYER_JUMP = 12.3;
    float DAMPING = 0.8;
    float RESTING_ROPE_LENGTH = 0.1;
    float GRAPPLING_HOOK_SPEED = 1000;
    float WINDOW_HEIGHT = 720;
    float WINDOW_WIDTH = 1280;
    float FRICTION_COEFFICIENT = 0.1;
    int SPRITE_SCALE = 5;
    float MINIMUM_VELOCITY = 0.3;
    float FRAME_DURATION = .1;
    float COLLISION_BUFFER =  0.000046f;
    int TILE_SIZE = 16; // (px x px)
    int CHUNK_SIZE = 16; // (tile x tile)
}