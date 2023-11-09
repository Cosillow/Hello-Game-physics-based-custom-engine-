#include "rope.hpp"

Rope::Rope(int numLinks, const Vector2& position) :
UpdateableI()
, _position(position)
{
    for (int i = 0; i < numLinks; ++i)
    {
        this->_links.emplace_back(position);
    }
}

void Rope::update(float deltaTime)
{
    const auto maxX = this->_links.size() - 1;
    int i;
    for (i = 1; i < maxX; ++i)
    {
        this->_links[i].update(deltaTime);
    }

    for (i=0; i<50; ++i)
    {
        this->applyConstraints();    
    }
}

void Rope::applyConstraints()
{
    const auto maxX = this->_links.size() - 1;
    this->_links[0].setPosition(this->_position);

    for (int i = 0; i < maxX; ++i)
    {
        Body firstSeg = this->_links[i];
        Body secondSeg = this->_links[i+1];

        float dist = (firstSeg.getPosition() - secondSeg.getPosition()).magnitude();
        float error = dist - this->RopeSize;

        Vector2 changeDir = (firstSeg.getPosition() - secondSeg.getPosition()).normalize();
        Vector2 changeAmount = changeDir * error;

        if (i != 0)
        {
            firstSeg.setCurrentPosition(firstSeg.getPosition() - (changeAmount * 0.5f));
            this->_links[i] = firstSeg;

            secondSeg.setCurrentPosition(secondSeg.getPosition() + (changeAmount * 0.5f));
            this->_links[i + 1] = secondSeg;
        }
        else
        {
            secondSeg.setCurrentPosition(secondSeg.getPosition() + (changeAmount ));
            this->_links[i + 1] = secondSeg;

        }

        // Vector2 vec1 = this->_links[i - 1].getPosition() - this->_links[i].getPosition();

        // float Magnitude1 = vec1.magnitude();
        // float Extension1 = Magnitude1 - this->RopeSize;

        // Vector2 vec2 = this->_links[i + 1].getPosition() - this->_links[i].getPosition();

        // float Magnitude2 = vec2.magnitude();
        // float Extension2 = Magnitude2 - this->RopeSize;

        // Vector2 final = (vec1 / Magnitude1 * Extension1) + (vec2 / Magnitude2 * Extension2);

        // this->_links[i].applyImpulse(final * 0.01);
    }
}