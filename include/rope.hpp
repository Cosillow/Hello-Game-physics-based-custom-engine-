#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "2dphysics.hpp"


class Rope : public UpdateableI
{
public:
    virtual ~Rope() { }
    Rope(Vector2 startPoint, float ropeSize);
    Rope(): Rope({0,0}, 0) { }

    virtual void update(float deltaTime);

    int getNumLinks() const { return _links.size(); }
    const std::vector<std::shared_ptr<Body>>& getLinks() const { return this->_links; }
    Body& getLink(int index) const { return *(this->_links[index]); }

    void setEnds(Body& startLink, Body& endLink);
    void setEnds(const Vector2& startPoint, const Vector2& endPoint);
    
    void setEndLink(Body* link) { this->_links[this->_links.size()-1] =  std::shared_ptr<Body>(link, [](Body* ptr) {delete ptr;}); }
    void setEndLink(const Vector2& position) { this->_links[this->_links.size()-1]->setPosition(position); }
    void setStartLink(Body* link) { this->_links[0] = std::shared_ptr<Body>(link, [](Body* ptr) {delete ptr;});; }
    void setStartLink(const Vector2& position) { this->_links[0]->setPosition(position); }

    Body getEndLink() const { return *(this->_links[0]); }
    Body getStartLink() const { return *(this->_links[this->_links.size()-1]); }

    friend std::ostream& operator<<(std::ostream& os, const Rope& rope) {
        os << "number links: " << rope.getLinks().size() << " start: " << rope.getStartLink() << ", end: " << rope.getEndLink() << std::endl;
        return os;
    }

private:
    std::vector<std::shared_ptr<Body>> _links;
};
