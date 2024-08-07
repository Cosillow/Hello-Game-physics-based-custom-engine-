#include <string>
#include "constants.hpp"


namespace Constants {
    bool debugMode = false;
    float PLAYER_SPEED = 20.0;
    float PLAYER_MAX_SPEED = 10.0;
    float FRICTION = 0.5;
    float GRAVITY = 130.0; 
    float PLAYER_JUMP = 24;
    float DAMPING = 0.8;
    float RESTING_ROPE_LENGTH = 0.1;
    float GRAPPLING_HOOK_SPEED = 1000;
    float WINDOW_HEIGHT = 720;
    float WINDOW_WIDTH = 1280;
    int SPRITE_SCALE = 2;
    float MINIMUM_VELOCITY = 0.3;
    float FRAME_DURATION = .1;
    float COLLISION_BUFFER =  0.000046f;
    int TILE_SIZE = 16; // (px x px)
    int CHUNK_SIZE = 16; // (tile x tile)
    std::string basePath = "";
    float GAME_HEIGHT = 10000;
    float GAME_WIDTH = 10000;
}