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
    if (this->_currentState == State::FreeFall) {
        Body::applyForce(Constants::GRAVITY);
    }

    

    Body::update(deltaTime);

    if (_isMovingLeft) {
        this->Body::setPosition(this->getPosition() - Vector2(Constants::PLAYER_SPEED, 0));
    } if (_isMovingRight) {
        this->Body::setPosition(this->getPosition() + Vector2(Constants::PLAYER_SPEED, 0));
    }
    
    if (_equippedItem) _equippedItem->update(deltaTime);
    
    
}

void Player::jump() {
    if (this->_currentState == State::TouchingGround) {
        this->_currentState = State::FreeFall;
        this->Body::applyImpulse({0.0, -Constants::PLAYER_JUMP});
    }
}

void Player::setLookAngle(const Vector2& mousePosition)
{
    _lookAngle = this->getPosition().calculateAngle(mousePosition);
}
