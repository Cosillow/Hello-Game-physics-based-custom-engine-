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
    Entity::update(deltaTime);

    const float speed = Constants::PLAYER_SPEED * deltaTime;

    SDL_FPoint playerPosition = Entity::getPosition();
    
    if (_isMovingUp) {
        playerPosition.y -= speed;
    } if (_isMovingDown) {
        playerPosition.y += speed;
    } if (_isMovingLeft) {
        playerPosition.x -= speed;
    } if (_isMovingRight) {
        playerPosition.x += speed;
    }
    Entity::setPosition(playerPosition);

    if (_weapon) _weapon->update(deltaTime);
}

void Player::jump() {
    if (this->_currentState == State::TouchingGround) {
        this->_currentState = State::FreeFall;
        this->addForce(ForceType::Gravity);
        this->Entity::applyImpulse({0.0, -Constants::PLAYER_JUMP});
        // this->addForce(ForceType::Jump);
    }
}