#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


#include "player.hpp"
#include "inputmanager.hpp"
#include "constants.hpp"

void Player::moveRight(bool start) {
    if (!this->_isMovingRight && start) {
        // player just started moving
        this->applyForce(Vector2(Constants::PLAYER_SPEED, 0));
    } else if (this->_isMovingRight && !start) {
        // player stops moving
        this->applyForce(Vector2(-Constants::PLAYER_SPEED, 0));
    }
    this->_isMovingRight = start;
}

void Player::moveLeft(bool start) {
    if (!this->_isMovingLeft && start) {
        // player just started moving
        this->applyForce(Vector2(-Constants::PLAYER_SPEED, 0));
    } else if (this->_isMovingLeft && !start) {
        // player stops moving
        this->applyForce(Vector2(Constants::PLAYER_SPEED, 0));
    }
    this->_isMovingLeft = start;
}

void Player::update(float deltaTime) {

    Body::update(deltaTime);    
    
    if (_equippedItem) _equippedItem->update(deltaTime);
    
    
}

void Player::jump() {
    if (this->isTouchingGround()) {
        this->setIsTouchingGround(false);
        this->Body::applyImpulse({0.0, -Constants::PLAYER_JUMP});
    }
}

void Player::setLookAngle(const Vector2& mousePosition)
{
    _lookAngle = this->getPosition().calculateAngle(mousePosition);
}
