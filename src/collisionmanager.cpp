#include "collisionmanager.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "platform.hpp"

void CollisionManager::resolveBounds(Player& player) const
{
    Hitbox* hitbox = player.getHitbox();
    if (!hitbox) return;

    if (hitbox->getBottomY() >= Constants::WINDOW_HEIGHT) {
        // player hit the bottom of the window
        player.setIsTouchingGround(true);

        const float newYPosition = Constants::WINDOW_HEIGHT - (hitbox->_size.y / 2) + Constants::COLLISION_BUFFER;
        player.setOldPosition(Vector2(player.getOldPosition().x, newYPosition));
        player.setPosition(Vector2(player.getPosition().x, newYPosition));
    }
}

void CollisionManager::resolveBounds(Player& player, Platform& platform) const
{
    Hitbox* playerHitbox = player.getHitbox();
    Hitbox* platformHitbox = platform.getHitbox();

    if (!playerHitbox || !platformHitbox) return;
    
    if (playerHitbox->checkCollisions(*platformHitbox))
    {
        player.setIsTouchingGround(true);
        const float newYPosition = platformHitbox->getTopY() - (playerHitbox->_size.y / 2)+ Constants::COLLISION_BUFFER;
        player.setOldPosition(Vector2(player.getOldPosition().x, newYPosition));
        player.setPosition(Vector2(player.getPosition().x, newYPosition));
    }
}
