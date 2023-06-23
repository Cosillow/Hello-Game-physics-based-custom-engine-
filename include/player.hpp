#pragma once
#include <SDL2/SDL.h>
#include "2dphysics.hpp"
#include "item.hpp"
#include "resourcemanager.hpp"
#include "animatedsprite.hpp"
#include "constants.hpp"

class Player: public Body, public AnimatedSpriteContainer
{
public:
    Player(Vector2 pos): Body(pos), AnimatedSpriteContainer(AnimatedSprite(ResourceManager::getInstance().getTexture("first-run-animation-Sheet"), 32, 32, 8)),
    _lookAngle(0),
    _movingLeft(Vector2()), 
    _movingRight(Vector2()),
    _equippedItem(nullptr) { this->addHitboxBB(32 * Constants::SPRITE_SCALE, 32 * Constants::SPRITE_SCALE); }

    Player(): Player(Vector2()) {}

    void moveLeft(bool start);
    void moveRight(bool start);
    void jump();

    void equipItem(Item* item) { _equippedItem = item; }


    void setLookAngle(const Vector2& mousePosition);
    void attack() { if (this->_equippedItem) this->_equippedItem->use(); }
    void update(float deltaTime) override;
    void setPosition(const Vector2& pos) override { this->Body::setPosition(pos); if (_equippedItem) this->_equippedItem->update(0); }

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
