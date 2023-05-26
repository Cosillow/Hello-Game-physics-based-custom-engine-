#pragma once

#include <vector>
#include "entity.hpp"

class Rope : public Entity
{
public:
    virtual ~Rope() { Entity::~Entity(); }
    Rope(Vector2 pos, int numLinks);
    void update(float deltaTime) override;

    int getNumLinks() const { return _links.size(); }
    const std::vector<Entity>& getLinks() const { return _links; }
    const Entity& getLink(int index) const { return _links[index]; }
    void setAnchorPoints(const Vector2& startAnchor, const Vector2& endAnchor);

    Vector2 getEndAnchor() const { return _endAnchor; }
    Vector2 getStartAnchor() const { return _startAnchor; }

private:
    std::vector<Entity> _links;
    Vector2 _startAnchor;
    Vector2 _endAnchor;
};
