#include "rope.hpp"
#include "constants.hpp"

Rope::Rope(int numLinks, const Vector2& position) :
UpdateableI()
, _position(position)
{
    for (int i = 0; i < numLinks; ++i)
    {
        auto point = std::make_shared<Body>(position + Vector2(0, (i * this->RopeSize)));
        point->addHitboxBB(1, 1);
        // point->applyForce({0, -Constants::GRAVITY* 2}); // balloon
        point->applyForce({0, -Constants::GRAVITY * (0.5f)}); // reduced

        this->_links.push_back(point);
    }
}

void Rope::update(float deltaTime)
{
    const int maxX = this->_links.size() - 1;
    int i;
    for (auto& seg: this->_links)
    {
        seg->update(deltaTime);
    }

    for (i=0; i<50; ++i)
    {
        this->applyConstraints();    
    }
}

void Rope::applyConstraints()
{
    const int maxX = this->_links.size() - 1;
    this->_links[0]->setPosition(this->_position);

    for (int i = 0; i < maxX; ++i)
    {
        Body& firstSeg = *this->_links[i];
        Body& secondSeg = *this->_links[i+1];

        float dist = (firstSeg.getPosition() - secondSeg.getPosition()).magnitude();
        float error = dist - this->RopeSize;

        Vector2 changeDir = (firstSeg.getPosition() - secondSeg.getPosition()).normalize();
        Vector2 changeAmount = changeDir * error;

        if (i != 0)
        {
            firstSeg.setCurrentPosition(firstSeg.getPosition() - (changeAmount * 0.5f));
            secondSeg.setCurrentPosition(secondSeg.getPosition() + (changeAmount * 0.5f));
        }
        else
        {
            secondSeg.setCurrentPosition(secondSeg.getPosition() + (changeAmount));
        }
    }
}