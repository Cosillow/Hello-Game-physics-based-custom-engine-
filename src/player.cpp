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

    Vector2 playerPosition = Entity::getPosition();
    
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

    if (_equippedItem) _equippedItem->update(deltaTime);
}

void Player::jump() {
    if (this->_currentState == State::TouchingGround) {
        this->_currentState = State::FreeFall;
        this->addForce(ForceType::Gravity);
        this->Entity::applyImpulse({0.0, -Constants::PLAYER_JUMP});
        // this->addForce(ForceType::Jump);
    }
}

void Player::lookDirection(int mouseX, int mouseY)
{
    // Calculate the center position of the player's rectangle
    int centerX = this->getPosition().x + this->getBoundingBox().w / 2;
    int centerY = this->getPosition().y + this->getBoundingBox().h / 2;

    // Calculate the offset between the mouse position and the center of the player's rectangle
    float dx = static_cast<float>(mouseX) - static_cast<float>(centerX);
    float dy = static_cast<float>(mouseY) - static_cast<float>(centerY);

    // Calculate the angle between the player's position and the mouse position
    float angle = std::atan2(dy, dx);

    // Store as degree value
    _lookAngle = static_cast<int>(angle * 180.0f / M_PI);
}
