#pragma once
#include "weapon.hpp"
#include "player.hpp"

class Sword : public Weapon
{
public:
    Sword(SDL_FPoint offset, Texture& tex, Player& player): Weapon(player.getPosition(), tex), 
    _offset(offset),
    _player(player), 
    _swingTime(0.5f), 
    _swingTimer(0.0f) {}

    void attack() override;
    void block() override;
    void update(float deltaTime) override;

private:
    SDL_FPoint _offset;
    Player& _player;
    float _swingTime;
    float _swingTimer;
};
