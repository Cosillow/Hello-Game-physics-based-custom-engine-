#pragma once
#include <SDL2/SDL.h>
#include "entity.hpp"
#include "weapon.hpp"

class Player : public Entity
{
public:
    enum class State
    {
        FreeFall,
        TouchingGround
    };
    Player(SDL_FPoint pos, Texture& tex): Entity(pos, tex), 
    _isMovingUp(false), 
    _isMovingDown(false), 
    _isMovingLeft(false), 
    _isMovingRight(false),
    _weapon(nullptr),
    _currentState(State::FreeFall) { Entity::addForce(Entity::ForceType::Gravity); }

    void moveUp(bool start);
    void moveDown(bool start);
    void moveLeft(bool start);
    void moveRight(bool start);
    void jump();

    void equipWeapon(Weapon* weapon) { _weapon = weapon; }
    Weapon* getWeapon() const { return _weapon; }
    State getState() const { return _currentState; }

    void update(float deltaTime) override;
    inline void setPosition(const SDL_FPoint& pos) override { this->Entity::setPosition(pos); if (_weapon) this->_weapon->update(0); }
    void setState(State state) { _currentState = state; }
private:
    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight;
    Weapon* _weapon;
    State _currentState;
};
