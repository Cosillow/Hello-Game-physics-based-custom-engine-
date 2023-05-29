#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "rope.hpp"
#include "constants.hpp"
#include "2dphysics.hpp"


Rope::Rope(Vector2 startPoint, Vector2 endPoint, int numLinks): UpdateableI(),
_links({})
{
    // Create and initialize the links of the rope
    // make the endpoints static bodies
    Vector2 direction = (endPoint - startPoint).normalize();
    float totalLength = (endPoint - startPoint).magnitude();
    for (int i = 0; i < numLinks; ++i) {
        float t = i / static_cast<float>(numLinks - 1);
        Vector2 position = startPoint + direction * (t * totalLength);

        // set the two endpoints as static
        this->_links.push_back( std::make_shared<Body>(position, Constants::ROPE_MASS, (i == 0 || i == numLinks - 1)));
    }
}

void Rope::update(float deltaTime)
{
    int numLinks = _links.size();
    for (int i = 0; i < numLinks; ++i) {
        Body& currentLink = *(this->_links[i]);


        // Vector2 lastPosition = this->_links[(i - 1 + numLinks) % numLinks]->getPosition() - currentLink.getPosition();
        // Vector2 nextPosition = this->_links[(i + 1) % numLinks]->getPosition() - currentLink.getPosition();

        // float extension1 = (lastPosition.magnitude() - Constants::RESTING_ROPE_LENGTH) / lastPosition.magnitude();
        // float extension2 = (nextPosition.magnitude() - Constants::RESTING_ROPE_LENGTH) / nextPosition.magnitude();


        // Vector2 newVelocity = (lastPosition.normalize() * extension1) + (nextPosition.normalize() * extension2);

        
        Vector2 lastPosition = this->_links[(i - 1 + numLinks) % numLinks]->getPosition() - currentLink.getPosition();
        float extension1 = lastPosition.magnitude() - Constants::RESTING_ROPE_LENGTH;
        Vector2 nextPosition = this->_links[(i + 1) % numLinks]->getPosition() - currentLink.getPosition();
        float extension2 = nextPosition.magnitude() - Constants::RESTING_ROPE_LENGTH;
        Vector2 newVelocity = (lastPosition / lastPosition.magnitude() * extension1) + (nextPosition / nextPosition.magnitude() * extension2);


        currentLink.applyForce(Constants::GRAVITY);
        currentLink.setVelocity(currentLink.getVelocity() * Constants::DAMPING + (newVelocity ));
        currentLink.setPosition(currentLink.getPosition() + currentLink.getVelocity() * deltaTime);


        currentLink.update(deltaTime);
    }
}


void Rope::setEnds(const Vector2& startPoint, const Vector2& endPoint)
{
    this->setEndLink(startPoint);
    this->setEndLink(endPoint);
}   

void Rope::setEnds(Body& startLink, Body& endLink) {
    this->setStartLink(&startLink);
    this->setEndLink(&endLink);
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
