#include <SDL2/SDL.h>
#include <vector>
#include "rope.hpp"
#include "constants.hpp"
#include "2dphysics.hpp"


Rope::Rope(Vector2 startPoint, Vector2 endPoint, int numLinks): UpdateableI(),
_links({}),
_startAnchor(startPoint), 
_endAnchor(endPoint)
{
    // Create and initialize the links of the rope
    // make the endpoints static bodies
    Vector2 direction = (_endAnchor - _startAnchor).normalize();
    float totalLength = (_endAnchor - _startAnchor).magnitude();
    for (int i = 0; i < numLinks; ++i) {
        float t = i / static_cast<float>(numLinks - 1);
        Vector2 position = _startAnchor + direction * (t * totalLength);
        Body currentLink(position, Constants::ROPE_MASS, (i == 0 || i == numLinks - 1));      

        this->_links.push_back(currentLink);
    }
}

Rope::Rope(Vector2 pos, int numLinks): Rope(pos, pos, numLinks) {}

void Rope::update(float deltaTime)
{
    int numLinks = _links.size();
    for (int i = 0; i < numLinks; ++i) {
        Body& currentLink = _links[i];

        currentLink.applyForce(Constants::GRAVITY);
        Vector2 lastPosition = this->_links[(i - 1 + numLinks) % numLinks].getPosition() - currentLink.getPosition();
        float extension1 = lastPosition.magnitude() - Constants::RESTING_ROPE_LENGTH;
        Vector2 nextPosition = this->_links[(i + 1) % numLinks].getPosition() - currentLink.getPosition();
        float extension2 = nextPosition.magnitude() - Constants::RESTING_ROPE_LENGTH;
        Vector2 newVelocity = (lastPosition / lastPosition.magnitude() * extension1) + (nextPosition / nextPosition.magnitude() * extension2);

        currentLink.setVelocity(currentLink.getVelocity() * Constants::DAMPING + (newVelocity ));
        currentLink.setPosition(currentLink.getPosition() + currentLink.getVelocity() * deltaTime);


        currentLink.update(deltaTime);
    }
}


void Rope::setAnchorPoints(const Vector2& startAnchor, const Vector2& endAnchor)
{
    _startAnchor = startAnchor;
    _endAnchor = endAnchor;
}

// void Rope::setLinkPosition(int index, const Vector2& position)
// {
//     if (index >= 0 && index < _links.size()) {
//         _links[index].position = position;
//     }
// }

// void Rope::setLinkVelocity(int index, const Vector2& velocity)
// {
//     if (index >= 0 && index < _links.size()) {
//         _links[index].velocity = velocity;
//     }
// }
