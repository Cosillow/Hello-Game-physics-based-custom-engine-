#include "collisionmanager.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "platform.hpp"

void CollisionManager::resolveBounds(Player& player) const
{
    Hitbox* hitbox = player.getHitbox();
    if (!hitbox) return;

    // resolve bounds of game world
    if (hitbox->getBottomY() >= Constants::GAME_HEIGHT)
    {
        player.setIsTouchingGround(true);

        const float newYPosition = Constants::GAME_HEIGHT - (hitbox->_size.y / 2);
        player.setPositionY(newYPosition);
    }
    if (hitbox->getTopY() <= 0)
    {
        const float newYPosition = (hitbox->_size.y / 2);
        player.setPositionY(newYPosition);   
    }
    if (hitbox->getRightX() >= Constants::GAME_WIDTH)
    {
        const float newXPosition = Constants::GAME_WIDTH - (hitbox->_size.x / 2);
        player.setPositionX(newXPosition);   
    }
    if (hitbox->getLeftX() <= 0)
    {
        const float newXPosition = (hitbox->_size.x / 2);
        player.setPositionX(newXPosition);   
    }
}

void CollisionManager::resolveBounds(Player& player, Platform& platform) const
{
    Hitbox* playerHitbox = player.getHitbox();
    Hitbox* platformHitbox = platform.getHitbox();

    if (!playerHitbox || !platformHitbox)
        return;
    if (!playerHitbox->checkCollisions(*platformHitbox))
        return;
        
    player.setIsTouchingGround(true);
    const float newYPosition = platformHitbox->getTopY() - (playerHitbox->_size.y / 2)+ Constants::COLLISION_BUFFER;
    player.setPositionY(newYPosition);
}
