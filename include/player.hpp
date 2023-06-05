#pragma once
#include <SDL2/SDL.h>
#include "2dphysics.hpp"
#include "item.hpp"
#include "resourcemanager.hpp"
#include "sprite.hpp"
#include "constants.hpp"

class SpriteContainer;

class Player : public Body, public SpriteContainer
{
public:
    Player(Vector2 pos): Body(pos), SpriteContainer(Sprite(ResourceManager::getInstance().getTexture("monkey"))),
    _lookAngle(0),
    _isMovingLeft(false), 
    _isMovingRight(false),
    _equippedItem(nullptr) { this->addHitboxBB(16 * Constants::SPRITE_SCALE, 32 * Constants::SPRITE_SCALE); }

    void moveLeft(bool start);
    void moveRight(bool start);
    void jump();

    void equipItem(Item* item) { _equippedItem = item; }
    Item* getEquippedItem() const { return _equippedItem; }
    int getLookAngle() const { return _lookAngle; }

    void setLookAngle(const Vector2& mousePosition);
    void attack() { if (this->_equippedItem) this->_equippedItem->use(); }
    virtual void update(float deltaTime);
    virtual inline void setPosition(const Vector2& pos) { this->Body::setPosition(pos); if (_equippedItem) this->_equippedItem->update(0); }
private:
    int _lookAngle;
    bool _isMovingLeft;
    bool _isMovingRight;
    Item* _equippedItem;
    Sprite _sprite;
};
