#pragma once

#include <vector>
#include "entity.hpp"

class Rope : public Entity
{
public:
    virtual ~Rope() { Entity::~Entity(); }
    Rope(SDL_FPoint pos, int numLinks);
    void update(float deltaTime) override;

    int getNumLinks() const { return _links.size(); }
    const std::vector<Entity>& getLinks() const { return _links; }
    const Entity& getLink(int index) const { return _links[index]; }
    void setAnchorPoints(const SDL_FPoint& startAnchor, const SDL_FPoint& endAnchor);

    SDL_FPoint getEndAnchor() const { return _endAnchor; }
    SDL_FPoint getStartAnchor() const { return _startAnchor; }

private:
    std::vector<Entity> _links;
    SDL_FPoint _startAnchor;
    SDL_FPoint _endAnchor;
};
