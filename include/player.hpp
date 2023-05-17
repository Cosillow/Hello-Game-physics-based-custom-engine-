#pragma once
#include <SDL2/SDL.h>

#include "entity.hpp"


class Player : public Entity
{
public:
    Player(int x, int y, Texture& tex, int playerID): Entity(Vector2f(x, y), tex), _id(playerID) {  };
    void moveUp(bool start);
    void moveDown(bool start);
    void moveLeft(bool start);
    void moveRight(bool start);
    int getId() {return _id;}
    void update(float deltaTime) override;
private:
    int _id;
    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight; 
};