#include "sword.hpp"
#include "item.hpp"

void Sword::use(bool endUse) { }

void Sword::useSecondary(bool endUse) { }

void Sword::update(float deltaTime)
{
    Vector2 swordPos = getPosition();
    Vector2 playerPos = _player.getPosition();

    // Sword is not swinging, update position
    swordPos.x = playerPos.x + _offset.x;
    swordPos.y = playerPos.y + _offset.y;

    setPosition(swordPos);
}
