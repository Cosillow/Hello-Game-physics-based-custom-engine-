#include "collisionmanager.hpp"
#include "player.hpp"

// bool CollisionManager::checkAndResolve(Entity& entity1, Entity& entity2) const
// {
//     const SDL_Rect& rect1 = entity1.getBoundingBox();
//     const SDL_Rect& rect2 = entity2.getBoundingBox();

//     if (SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE) {
//         // Collision occurred, resolve it

//         // Calculate the minimum translation vector (MTV)
//         float mtvX = 0.0f;
//         float mtvY = 0.0f;

//         // Calculate the overlap between the entities
//         float overlapX = rect1.w + rect2.w - std::abs(rect1.x - rect2.x) - 1;
//         float overlapY = rect1.h + rect2.h - std::abs(rect1.y - rect2.y) - 1;

//         // Determine the direction of the MTV
//         if (overlapX < overlapY) {
//             if (rect1.x < rect2.x) {
//                 mtvX = -overlapX;
//             } else {
//                 mtvX = overlapX;
//             }
//         } else {
//             if (rect1.y < rect2.y) {
//                 mtvY = -overlapY;
//             } else {
//                 mtvY = overlapY;
//             }
//         }

//         // Move the entities apart along the MTV
//         float massSum = entity1.getMass() + entity2.getMass();
//         float ratio1 = entity2.getMass() / massSum;
//         float ratio2 = entity1.getMass() / massSum;

//         SDL_FPoint separation1 = { mtvX * ratio1, mtvY * ratio1 };
//         SDL_FPoint separation2 = { mtvX * -ratio2, mtvY * -ratio2 };

//         entity1.applyImpulse(separation1);
//         entity2.applyImpulse(separation2);

        

//         return true; // Collision resolved
//     }

//     // Set velocities to zero to stop movement
//         // entity1.setVelocity({0,0});
//         // entity2.setVelocity({0,0});
//     return false; // No collision
// }

bool CollisionManager::resolveBounds(Player& player) const
{
    const SDL_Rect& rect = player.getBoundingBox();
    const int windowWidth = 1280;
    const int windowHeight = 720;

    SDL_Rect windowRect = { 0, 0, windowWidth, windowHeight };

    if (rect.x < 0 || rect.y < 0 || rect.x + rect.w > windowWidth || rect.y + rect.h > windowHeight)
    {
        // rect.x < 0 || rect.x + rect.w > windowWidth
        
        // Adjust the player's position to stay within the window bounds
        float x = player.getPosition().x;
        float y = player.getPosition().y;

        if (rect.x < 0)
            x = 0;
        else if (rect.x + rect.w > windowWidth)
            x = windowWidth - rect.w;

        if (rect.y < 0)
            y = 0;
        else if (rect.y + rect.h > windowHeight)
            y = windowHeight - rect.h;

        
        player.setPosition({ x, y });

        

        if ((rect.y + rect.h > windowHeight) && player.getState() == Player::State::FreeFall) {
            // player hit floot after free fall for first time
            player.removeForce(Entity::ForceType::Gravity);
            player.setState(Player::State::TouchingGround);
            player.setVelocity({ 0.0f, 0.0f });
            player.setAcceleration({0, 0});
        }
        
        return true;
    }
    else
    {
        return false; // No collision with walls
    }

    
}
