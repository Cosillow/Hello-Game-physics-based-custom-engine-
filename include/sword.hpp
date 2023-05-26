#pragma once
#include "item.hpp"
#include "player.hpp"
#include "renderwindow.hpp"

class Sword : public Item
{
public:
    Sword(Vector2 offset, Player& player): Item(player), 
    _offset(offset) {}

    virtual void use(bool endUse=false);
    virtual void useSecondary(bool endUse=false);
    virtual void update(float deltaTime);
    virtual void renderItem(RenderWindow& renderWindow) { renderWindow.render(*this); }

private:
    Vector2 _offset;
};
