#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include <cmath>
#include "rope.hpp"
#include "constants.hpp"
#include "2dphysics.hpp"

Rope::Rope(Vector2 startPoint, float ropeSize) : UpdateableI(),
_links({})
{
    // Create and initialize the links of the rope
    // make the endpoints static bodies
    Vector2 direction = {0, 1};
    int numLinks = std::ceil(ropeSize / Constants::RESTING_ROPE_LENGTH);
    for (int i = 0; i < numLinks; ++i)
    {
        Vector2 position = startPoint + (Vector2(0, Constants::RESTING_ROPE_LENGTH) * i);

        std::shared_ptr<Body> link = std::make_shared<Body>(position, 0);
        link->setVelocity(position); // set old position
        this->_links.push_back(link);
    }
}

void Rope::update(float deltaTime)
{
    int numLinks = _links.size();

    // Distance constraint which reduces iterations, but doesn't handle stretchyness in a natural way.
    // Body &firstLink = *(this->_links[0]);
    // Body &lastLink = *(this->_links[numLinks-1]);
    // float distance = firstLink.getPosition().distance(lastLink.getPosition());
    // if (distance > 0 && distance > numLinks * Constants::RESTING_ROPE_LENGTH) {
    //     Vector2 dir = (lastLink.getPosition() - firstLink.getPosition()).normalize();
    //     lastLink.setVelocity(firstLink.getPosition()); // set old position
    //     lastLink.setPosition(firstLink.getPosition() + (dir * numLinks * Constants::RESTING_ROPE_LENGTH));
    // }

    // simulate
    for (int i = 0; i < numLinks; i++)
    {
        Body &currentLink = *(this->_links[i]);

        Vector2 currentPosition = currentLink.getPosition();
        Vector2 oldPosition = currentLink.getVelocity();

        currentLink.setPosition(currentLink.getPosition() + (currentPosition - oldPosition) + Constants::GRAVITY * (deltaTime * deltaTime));
        currentLink.setVelocity(currentPosition); // set old position
    }

    // apply constraints
    for (int iterations = 20; iterations > 0; --iterations)
    {
        for (int i = 0; i < numLinks - 1; ++i)
        {
            Body &currentLink = *(this->_links[i]);
            Body &nextLink = *(this->_links[i + 1]);

            if (i == 0)
            { // && last link probably too ?
                // todo: set position to moving object or static location
                currentLink.setPosition({100, 200});
                currentLink.setVelocity({100, 200}); // set old position
            }

            // Current distance between rope nodes.
            Vector2 diff = currentLink.getPosition() - nextLink.getPosition();

            float dist = currentLink.getPosition().distance(nextLink.getPosition());
            float difference = 0;
            // Guard against divide by 0.
            if (dist > 0)
            {
                difference = (Constants::RESTING_ROPE_LENGTH - dist) / dist;
            }

            Vector2 translate = (diff * (.5f * difference)) * Constants::DAMPING;

            if (i != 0) currentLink.setPosition(currentLink.getPosition() + translate);
            nextLink.setPosition(nextLink.getPosition() - translate);
        }
    }
}

void Rope::setEnds(const Vector2 &startPoint, const Vector2 &endPoint)
{
    this->setEndLink(startPoint);
    this->setEndLink(endPoint);
}

void Rope::setEnds(Body &startLink, Body &endLink)
{
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
