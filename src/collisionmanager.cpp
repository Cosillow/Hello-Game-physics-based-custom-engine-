#include "collisionmanager.hpp"

bool CollisionManager::checkCollision(const Entity& entity1, const Entity& entity2)
{
    const SDL_Rect& rect1 = entity1.getBoundingBox();
    const SDL_Rect& rect2 = entity2.getBoundingBox();

    return SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE;
}
