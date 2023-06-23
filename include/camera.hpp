#pragma once

#include "2dphysics.hpp"
#include "tilemap.hpp"
#include "player.hpp"

class Camera
{
private:
    Vector2 _position;
    TileMap* _tileMap;
    Player* _player;

public:
    Camera(TileMap* tileMap, Player* player) : _tileMap(tileMap), _player(player) {}
    Camera(): Camera(nullptr, nullptr) {}
    ~Camera() {} // not in charge of pointers
};
