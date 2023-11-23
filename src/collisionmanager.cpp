#include "collisionmanager.hpp"
#include "player.hpp"
#include "constants.hpp"
#include "platform.hpp"
#include "cloud.hpp"

void CollisionManager::resolveBounds(Player& player, Cloud& cloud) const
{
    Hitbox* playerHitbox = player.getHitbox();
    Hitbox* cloudHitbox = cloud.getHitbox();

    if (!playerHitbox || !cloudHitbox)
        return;
    if (!playerHitbox->checkCollisions(*cloudHitbox))
        return;


}

void CollisionManager::resolveBounds(Body& body) const
{
    Hitbox* hitbox = body.getHitbox();
    if (!hitbox) return;

    // resolve bounds of game world
    if (hitbox->getBottomY() >= Constants::GAME_HEIGHT)
    {
        const float newYPosition = Constants::GAME_HEIGHT - (hitbox->_size.y / 2.0f);
        body.setPositionY(newYPosition);
    }
    if (hitbox->getTopY() <= 0)
    {
        const Vector2 v = body.getVelocity();
        // const float newYPosition = (hitbox->_size.y / 2.0f);
        const float newYPosition = Constants::GAME_HEIGHT - (hitbox->_size.y / 2.0f);
        body.setPositionY(newYPosition);
        body.setVelocity(v);
    }
    if (hitbox->getRightX() >= Constants::GAME_WIDTH)
    {
        const float newXPosition = Constants::GAME_WIDTH - (hitbox->_size.x / 2.0f);
        body.setPositionX(newXPosition);   
    }
    if (hitbox->getLeftX() <= 0)
    {
        const float newXPosition = (hitbox->_size.x / 2.0f);
        body.setPositionX(newXPosition);   
    }
}

void CollisionManager::resolveBounds(Body& body, Platform& platform) const
{
    Hitbox* bodyHitbox = body.getHitbox();
    Hitbox* platformHitbox = platform.getHitbox();

    if (!bodyHitbox || !platformHitbox)
        return;
    if (!bodyHitbox->checkCollisions(*platformHitbox))
    {
        return;
    }
        
        
    Vector2 bodyCenter = body.getPosition();
    Vector2 platformCenter = platform.getPosition();

    // Calculate the distance between centers
    float diffX = bodyCenter.x - platformCenter.x;
    float diffY = bodyCenter.y - platformCenter.y;

    // Calculate the minimum distance to separate along X and Y
    float minXDist = (bodyHitbox->_size.x + platformHitbox->_size.x) / 2.0f;
    float minYDist = (bodyHitbox->_size.y + platformHitbox->_size.y) / 2.0f;

    // Calculate the depth of collision for both the X and Y axis
    float depthX = diffX > 0 ? minXDist - diffX : - minXDist - diffX;
    float depthY = diffY > 0 ? minYDist - diffY : - minYDist - diffY;

    if (depthX != 0 && depthY != 0)
    {
        if (std::abs(depthX) < std::abs(depthY))
        {
            if (depthX > 0)
            {
                const float newXPosition = platformHitbox->getRightX() + (bodyHitbox->_size.x / 2.0f);
                body.setPositionX(newXPosition);
            } else
            {
                const float newXPosition = platformHitbox->getLeftX() - (bodyHitbox->_size.x / 2.0f);
                body.setPositionX(newXPosition);
            }
        } else
        {
            if (depthY > 0)
            {
                const float newYPosition = platformHitbox->getBottomY() + (bodyHitbox->_size.y / 2.0f);
                body.setPositionY(newYPosition); 
                
            } else
            {
                const float newYPosition = platformHitbox->getTopY() - (bodyHitbox->_size.y / 2.0f);
                body.setPositionY(newYPosition);
            }
        }
    }
}
