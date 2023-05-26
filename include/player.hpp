#pragma once
#include <SDL2/SDL.h>
#include "entity.hpp"
#include "item.hpp"

class Player : public Entity
{
public:
    enum class State
    {
        FreeFall,
        TouchingGround
    };
    Player(Vector2 pos): Entity(pos), 
    _lookAngle(0),
    _isMovingUp(false), 
    _isMovingDown(false), 
    _isMovingLeft(false), 
    _isMovingRight(false),
    _equippedItem(nullptr),
    _currentState(State::FreeFall) { Entity::addForce(Entity::ForceType::Gravity); }

    void moveUp(bool start);
    void moveDown(bool start);
    void moveLeft(bool start);
    void moveRight(bool start);
    void jump();

    void equipItem(Item* item) { _equippedItem = item; }
    Item* getEquippedItem() const { return _equippedItem; }
    State getState() const { return _currentState; }
    int getLookAngle() const { return _lookAngle; }

    void lookDirection(int mouseX, int mouseY);
    void attack() { if (this->_equippedItem) this->_equippedItem->use(); }
    void update(float deltaTime) override;
    inline void setPosition(const Vector2& pos) override { this->Entity::setPosition(pos); if (_equippedItem) this->_equippedItem->update(0); }
    void setState(State state) { _currentState = state; }
private:
    int _lookAngle;
    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight;
    Item* _equippedItem;
    State _currentState;
};
