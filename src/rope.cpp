#include <SDL2/SDL.h>
#include "rope.hpp"
#include "constants.hpp"
#include "entity.hpp"


Rope::Rope(SDL_FPoint pos, int numLinks) : Entity(pos), _startAnchor(pos), _endAnchor(pos)
{
    // Create and initialize the links of the rope
    _links.resize(numLinks);
    for (int i = 0; i < numLinks; ++i) {
        Entity& currentLink = _links[i];

        // Initialize position, velocity, and other properties of each link
        currentLink.setPosition({0.0f, i * Constants::RESTING_ROPE_LENGTH});
        currentLink.setVelocity({0.0f, 0.0f});
    }
}

void Rope::update(float deltaTime)
{
    int numLinks = _links.size();

    for (int i = 0; i < numLinks; ++i) {
        Entity& currentLink = _links[i];

        const SDL_FPoint& currentPosition = currentLink.getPosition();
        const SDL_FPoint& currentVelocity = currentLink.getVelocity();

        float X_Vector1 = _links[(i - 1 + numLinks) % numLinks].getPosition().x - currentPosition.x;
        float Y_Vector1 = _links[(i - 1 + numLinks) % numLinks].getPosition().y - currentPosition.y;
        float Magnitude1 = SDL_sqrt(X_Vector1 * X_Vector1 + Y_Vector1 * Y_Vector1);
        float Extension1 = Magnitude1 - Constants::RESTING_ROPE_LENGTH;

        float X_Vector2 = _links[(i + 1) % numLinks].getPosition().x - currentPosition.x;
        float Y_Vector2 = _links[(i + 1) % numLinks].getPosition().y - currentPosition.y;
        float Magnitude2 = SDL_sqrt(X_Vector2 * X_Vector2 + Y_Vector2 * Y_Vector2);
        float Extension2 = Magnitude2 - Constants::RESTING_ROPE_LENGTH;

        float xv = (X_Vector1 / Magnitude1 * Extension1) + (X_Vector2 / Magnitude2 * Extension2);
        float yv = (Y_Vector1 / Magnitude1 * Extension1) + (Y_Vector2 / Magnitude2 * Extension2) + Constants::GRAVITY;

        currentLink.setVelocity({currentVelocity.x * Constants::DAMPING + (xv * 0.001f),
                                 currentVelocity.y * Constants::DAMPING + (yv * 0.001f)});

        currentLink.setPosition({currentPosition.x + currentVelocity.x * deltaTime,
                                 currentPosition.y + currentVelocity.y * deltaTime});
    }

    // Update anchor positions based on entity position
    // _startAnchor = getPosition();
    // _endAnchor = getPosition(); // Modify this to set the end anchor position as needed
}


void Rope::setAnchorPoints(const SDL_FPoint& startAnchor, const SDL_FPoint& endAnchor)
{
    _startAnchor = startAnchor;
    _endAnchor = endAnchor;
}

// void Rope::setLinkPosition(int index, const SDL_FPoint& position)
// {
//     if (index >= 0 && index < _links.size()) {
//         _links[index].position = position;
//     }
// }

// void Rope::setLinkVelocity(int index, const SDL_FPoint& velocity)
// {
//     if (index >= 0 && index < _links.size()) {
//         _links[index].velocity = velocity;
//     }
// }
