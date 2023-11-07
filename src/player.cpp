#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


#include "player.hpp"
#include "inputmanager.hpp"
#include "constants.hpp"

void Player::moveRight(bool start)
{
    Vector2 force = Vector2(Constants::PLAYER_SPEED, 0);

    if (!this->isMovingRight() && start)
    {
        // player just started moving right
        this->_animatedSprite.setMirrorX(false);
        this->_movingRight = force;
        this->applyForce(force);
        this->setVelocity(Vector2(0, this->getVelocity().y));
    } else if (this->isMovingRight() && !start)
    {
        // player stops moving right
        this->applyForce(this->_movingRight * -1); // cancel previous force
        this->_movingRight = Vector2();
    }
}

void Player::moveLeft(bool start)
{
    Vector2 force = Vector2(-Constants::PLAYER_SPEED, 0);

    if (!this->isMovingLeft() && start)
    {
        // player just started moving left
        this->_animatedSprite.setMirrorX(true);
        this->_movingLeft = force;
        this->applyForce(force);
        this->setVelocity(Vector2(0, this->getVelocity().y));
    } else if (this->isMovingLeft() && !start)
    {
        // player stops moving left
        this->applyForce(this->_movingLeft * -1); // cancel previous force
        this->_movingLeft = Vector2();
    }
}

void Player::update(float deltaTime)
{
    this->Body::update(deltaTime);
    this->_animatedSprite.update(deltaTime);
    
    Vector2 newVelocity = this->getVelocity();
    bool faseterThanMax = std::abs(newVelocity.x) > Constants::PLAYER_MAX_SPEED;
    if (faseterThanMax)
    {
        newVelocity.x = (newVelocity.x > 0) ? Constants::PLAYER_MAX_SPEED : -Constants::PLAYER_MAX_SPEED;
        this->setVelocity(newVelocity);
    }
}

void Player::jump()
{
    if (this->isTouchingGround())
    {
        this->setIsTouchingGround(false);
        this->Body::applyImpulse({0.0, -Constants::PLAYER_JUMP});
    }
}

void Player::setLookAngle(const Vector2& mousePosition)
{
    _lookAngle = this->getPosition().calculateAngle(mousePosition);
}
