#include "collisionmanager.hpp"
#include "player.hpp"
#include "constants.hpp"

void CollisionManager::resolveBounds(Player& player) const
{
    Hitbox* hitbox = player.getHitbox();
    if (!hitbox) return;

    if (hitbox->getBottomY() >= Constants::WINDOW_HEIGHT) {
        // player hit the bottom of the window
        player.setIsTouchingGround(true);

        const float newYPosition = Constants::WINDOW_HEIGHT - (hitbox->_size.y / 2);
        player.setOldPosition(Vector2(player.getOldPosition().x, newYPosition));
        player.setPosition(Vector2(player.getPosition().x, newYPosition));

        // Apply friction force in the opposite x-direction
        // if (player.getVelocity().x != 0.0f) {
        //     const Vector2 frictionForce = player.getVelocity().normalize() * Constants::PLAYER_FRICTION * -1;
        //     player.applyForce(frictionForce);
        // }
    }
}
