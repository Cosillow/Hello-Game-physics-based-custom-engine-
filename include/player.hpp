#pragma once
#include <SDL2/SDL.h>

#include "entity.hpp"
#include "weapon.hpp" // Include the necessary header for Weapon

class Player : public Entity
{
public:
    Player(Vector2f pos, Texture& tex, int playerID)
        : Entity(pos, tex), _id(playerID),
          _isMovingUp(false), _isMovingDown(false), _isMovingLeft(false), _isMovingRight(false),
          _weapon(nullptr) // Initialize weapon pointer to nullptr
    {}

    void moveUp(bool start);
    void moveDown(bool start);
    void moveLeft(bool start);
    void moveRight(bool start);
    int getId() { return _id; }

    void equipWeapon(Weapon* weapon) { _weapon = weapon; } // Method to equip a weapon
    Weapon* getWeapon() const { return _weapon; } // Method to retrieve the weapon

    void update(float deltaTime) override;

private:
    int _id;
    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight;
    Weapon* _weapon; // Weapon member variable as a pointer
};
