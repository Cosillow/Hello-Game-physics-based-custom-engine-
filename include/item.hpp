#pragma once

#include "entity.hpp"

class Player;
class RenderWindow;

class Item : public Entity
{
public:
    Item(Player& player): Entity(),
    _player(player) {};
    virtual void use(bool endUse=false) = 0;
    virtual void useSecondary(bool endUse=false) = 0;
    virtual void update(float deltaTime) {};
    virtual void renderItem(RenderWindow& renderWindow) = 0;

    Player& getPlayer() { return _player; }
protected:
    Player& _player;
};
