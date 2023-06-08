#pragma once
#include <SDL2/SDL.h>
#include "2dphysics.hpp"
#include "item.hpp"
#include "resourcemanager.hpp"
#include "animatedsprite.hpp"
#include "constants.hpp"

class Player : public Body, public AnimatedSpriteContainer
{
public:
    Player(Vector2 pos): Body(pos), AnimatedSpriteContainer(AnimatedSprite(ResourceManager::getInstance().getTexture("chimpsheet"), 64, 64, 7)),
    _lookAngle(0),
    _movingLeft(Vector2()), 
    _movingRight(Vector2()),
    _equippedItem(nullptr) { this->addHitboxBB(64 * Constants::SPRITE_SCALE, 64 * Constants::SPRITE_SCALE); }

    void moveLeft(bool start);
    void moveRight(bool start);
    void jump();

    void equipItem(Item* item) { _equippedItem = item; }


    void setLookAngle(const Vector2& mousePosition);
    void attack() { if (this->_equippedItem) this->_equippedItem->use(); }
    virtual void update(float deltaTime);
    virtual inline void setPosition(const Vector2& pos) { this->Body::setPosition(pos); if (_equippedItem) this->_equippedItem->update(0); }

    // getters
    Item* getEquippedItem() const { return _equippedItem; }
    int getLookAngle() const { return _lookAngle; }
    bool isMovingLeft() const { return this->_movingLeft != Vector2(); }
    bool isMovingRight() const { return this->_movingRight != Vector2(); }
private:
    int _lookAngle;
    Vector2 _movingLeft;
    Vector2 _movingRight;
    Item* _equippedItem;
};
