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
        
    Vector2 playerCenter = player.getPosition();
    Vector2 platformCenter = platform.getPosition();

    // Calculate the distance between centers
    float diffX = playerCenter.x - platformCenter.x;
    float diffY = playerCenter.y - platformCenter.y;

    // Calculate the minimum distance to separate along X and Y
    float minXDist = (playerHitbox->_size.x + platformHitbox->_size.x) / 2;
    float minYDist = (playerHitbox->_size.y + platformHitbox->_size.y) / 2;

    // Calculate the depth of collision for both the X and Y axis
    float depthX = diffX > 0 ? minXDist - diffX : -minXDist - diffX;
    float depthY = diffY > 0 ? minYDist - diffY : -minYDist - diffY;

    if (depthX != 0 && depthY != 0)
    {
        if (std::abs(depthX) < std::abs(depthY))
        {
            if (depthX > 0)
            {
                const float newXPosition = platformHitbox->getRightX() + (playerHitbox->_size.x / 2);
                player.setPositionX(newXPosition);
            } else
            {
                const float newXPosition = platformHitbox->getLeftX() - (playerHitbox->_size.x / 2);
                player.setPositionX(newXPosition);
            }
        } else
        {
            if (depthY > 0)
            {
                const float newYPosition = platformHitbox->getBottomY() + (playerHitbox->_size.y / 2);
                player.setPositionY(newYPosition); 
                
            } else
            {
                player.setIsTouchingGround(true);
                const float newYPosition = platformHitbox->getTopY() - (playerHitbox->_size.y / 2);
                player.setPositionY(newYPosition);
            }
        }
    }
}
