#include "collisionmanager.hpp"
#include "player.hpp"
#include "constants.hpp"

void CollisionManager::resolveBounds(Player& player) const
{
    if (!player.getHitbox()) return;

    if (player.getHitbox()->getBottomY() >= Constants::WINDOW_HEIGHT) {
        // player hit floor after free fall for first time
        player.setState(Player::State::TouchingGround);
        player.setVelocity(player.getVelocity() * Vector2(1, 0));
    }
}
