#pragma once

class Platform;
class Cloud;
class Body;
class Player;

class CollisionManager
{
public:
    void resolveBounds(Body& body) const;
    void resolveBounds(Body& body, Platform& platform) const;
    void resolveBounds(Player& player, Cloud& cloud) const;
};
