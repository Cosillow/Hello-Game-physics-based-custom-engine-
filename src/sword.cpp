#include "sword.hpp"
#include "weapon.hpp"

void Sword::attack()
{
    _swingTimer = _swingTime; // Start the swing timer
    // Perform attack logic
}

void Sword::block()
{
    _blocking = true;
    // Perform block logic
}

void Sword::update(float deltaTime)
{
    Vector2f swordPos = getPos();
    Vector2f playerPos = _player.getPos();

    if (_swingTimer > 0.0f)
    {
        // Sword is swinging
        _swingTimer -= deltaTime;

        if (_swingTimer <= 0.0f)
        {
            // Swing animation complete
            _swingTimer = 0.0f;
        }
    }
    else
    {
        // Sword is not swinging, update position
        swordPos.x = playerPos.x + _offsetX;
        swordPos.y = playerPos.y + _offsetY;
    }

    // Set the updated sword position
    setPos(swordPos);
}
