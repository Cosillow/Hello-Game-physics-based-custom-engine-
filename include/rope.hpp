#pragma once

#include <vector>
#include "2dphysics.hpp"


class Rope : public UpdateableI
{
public:
    virtual ~Rope() { }
    Rope(Vector2 startPoint, Vector2 endPoint, int numLinks);
    Rope(Vector2 pos, int numLinks);
    Rope(): Rope({0,0}, 0) { }

    virtual void update(float deltaTime);

    int getNumLinks() const { return _links.size(); }
    const std::vector<Body>& getLinks() const { return this->_links; }
    const Body& getLink(int index) const { return this->_links[index]; }

    void setAnchorPoints(const Vector2& startAnchor, const Vector2& endAnchor);
    void setEndAnchor(const Vector2& anchor) { this->_endAnchor = anchor; }
    void setStartAnchor(const Vector2& anchor) { this->_startAnchor = anchor; }

    Vector2 getEndAnchor() const { return this->_endAnchor; }
    Vector2 getStartAnchor() const { return this->_startAnchor; }

    friend std::ostream& operator<<(std::ostream& os, const Rope& rope) {
        os << "number links: " << rope.getLinks().size() << "start: " << rope.getStartAnchor() << ", end: " << rope.getEndAnchor() << std::endl;
        return os;
    }

private:
    std::vector<Body> _links;
    Vector2 _startAnchor;
    Vector2 _endAnchor;
};
