#pragma once
#include <SDL2/SDL.h>
#include "2dphysics.hpp"
#include "item.hpp"
#include "resourcemanager.hpp"
#include "sprite.hpp"

class SpriteContainer;

class Player : public Body, public SpriteContainer
{
public:
    enum class State
    {
        FreeFall,
        TouchingGround
    };
    Player(Vector2 pos): Body(pos), SpriteContainer(Sprite(ResourceManager::getInstance().getTexture("monkey"))),
    _lookAngle(0),
    _isMovingUp(false), 
    _isMovingDown(false), 
    _isMovingLeft(false), 
    _isMovingRight(false),
    _equippedItem(nullptr),
    _currentState(State::FreeFall) { this->addHitboxBB(50, 200); }

    void moveUp(bool start);
    void moveDown(bool start);
    void moveLeft(bool start);
    void moveRight(bool start);
    void jump();

    void equipItem(Item* item) { _equippedItem = item; }
    Item* getEquippedItem() const { return _equippedItem; }
    State getState() const { return _currentState; }
    int getLookAngle() const { return _lookAngle; }

    void setLookAngle(const Vector2& mousePosition);
    void attack() { if (this->_equippedItem) this->_equippedItem->use(); }
    virtual void update(float deltaTime);
    virtual inline void setPosition(const Vector2& pos) { this->Body::setPosition(pos); if (_equippedItem) this->_equippedItem->update(0); }
    void setState(State state) { _currentState = state; }
private:
    int _lookAngle;
    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight;
    Item* _equippedItem;
    State _currentState;
    Sprite _sprite;
};
