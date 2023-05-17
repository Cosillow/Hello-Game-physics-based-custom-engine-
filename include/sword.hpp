#pragma once

#include "weapon.hpp"
#include "player.hpp"
#include "math.hpp"

class Sword : public Weapon
{
public:
    Sword(Vector2f pos, Texture& tex, Player& player): Weapon(pos, tex), _offsetX(0.0f), _offsetY(0.0f), _player(player), _swingTime(0.5f), _swingTimer(0.0f) {}
    void attack() override;
    void block() override;
    void update(float deltaTime) override;

private:
    float _offsetX;
    float _offsetY;
    Player& _player;
    float _swingTime;
    float _swingTimer;
};
