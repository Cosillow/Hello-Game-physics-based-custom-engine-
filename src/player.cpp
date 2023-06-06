#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


#include "player.hpp"
#include "inputmanager.hpp"
#include "constants.hpp"

void Player::moveRight(bool start) {
    // get through with nothing happening:
    // (isMovingRight && start) || (!isMovingRight && !start) || ()

    if (start && std::abs(this->getVelocity().x) >= Constants::PLAYER_MAX_SPEED) { this->applyForce(this->_movingRight * -1); // cancel previous force
        this->_movingRight = Vector2();std::cout<< "max speed" << std::endl;   return; }
    Vector2 force = Vector2(Constants::PLAYER_SPEED, 0);

    if (!this->isMovingRight() && start) {
        // player just started moving right
        this->_sprite.setMirrorX(false);
        this->_movingRight = force;
        this->applyForce(force);
    } else if (this->isMovingRight() && !start) {
        // player stops moving right
        this->applyForce(this->_movingRight * -1); // cancel previous force
        this->_movingRight = Vector2();
    }
}

void Player::moveLeft(bool start) {
    if (start && std::abs(this->getVelocity().x) >= Constants::PLAYER_MAX_SPEED) {this->applyForce(this->_movingLeft * -1); // cancel previous force
        this->_movingLeft = Vector2();std::cout<< "max speed" << std::endl;  return; }
    Vector2 force = Vector2(-Constants::PLAYER_SPEED, 0);

    if (!this->isMovingLeft() && start) {
        // player just started moving left
        this->_sprite.setMirrorX(true);
        this->_movingLeft = force;
        this->applyForce(force);
    } else if (this->isMovingLeft() && !start) {
        // player stops moving left
        this->applyForce(this->_movingLeft * -1); // cancel previous force
        this->_movingLeft = Vector2();
    }
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
