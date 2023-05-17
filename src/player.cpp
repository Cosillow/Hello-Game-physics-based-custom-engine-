#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


#include "player.hpp"
#include "inputmanager.hpp"
#include "constants.hpp"


void Player::moveUp(bool start) {
    _isMovingUp = start;
}

void Player::moveDown(bool start) {
    _isMovingDown = start;
}

void Player::moveRight(bool start) {
    _isMovingRight = start;
}

void Player::moveLeft(bool start) {
    _isMovingLeft = start;
}

void Player::update(float deltaTime) {
    const float speed = Constants::PLAYER_SPEED * deltaTime;

    if (_isMovingUp) {
        Entity::getPos().y -= speed;
    } if (_isMovingDown) {
        Entity::getPos().y += speed;
    } if (_isMovingLeft) {
        Entity::getPos().x -= speed;
    } if (_isMovingRight) {
        Entity::getPos().x += speed;
    }
}
