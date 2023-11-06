#include "2dphysics.hpp"
#include "player.hpp"
#include "memory"

class Camera: UpdateableI
{
public:
    Camera():
    UpdateableI()
    , _center({0,0})
    , _size({0,0})
    , _player(nullptr) {}

    Vector2 worldToScreen(const Vector2& world);
    void watchPlayer(const std::shared_ptr<Player>& player);

    void update(float deltaTime) override;

private:
    Vector2 _center;
    Vector2 _size;
    std::shared_ptr<Player> _player;
};