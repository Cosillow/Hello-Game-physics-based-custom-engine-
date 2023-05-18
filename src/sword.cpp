#include "sword.hpp"
#include "weapon.hpp"

#include <iostream>

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
    SDL_FPoint swordPos = getPosition();
    SDL_FPoint playerPos = _player.getPosition();

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
        swordPos.x = playerPos.x + _offset.x;
        swordPos.y = playerPos.y + _offset.y;
    }

    // Set the updated sword position
    std::cout << "sword position: " << swordPos.x << ", " << swordPos.y << std::endl;
    setPosition(swordPos);
}
