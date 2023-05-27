#pragma once

#include "2dphysics.hpp"
#include "constants.hpp"

class Player;
class RenderWindow;

class Item : public Body
{
public:
    Item(Player& player): Body(Constants::PLAYER_MASS),
    _player(player) {};
    virtual void use(bool endUse=false) = 0;
    virtual void useSecondary(bool endUse=false) = 0;
    virtual void update(float deltaTime) {};
    virtual void renderItem(RenderWindow& renderWindow) = 0;

    Player& getPlayer() { return _player; }
protected:
    Player& _player;
};
