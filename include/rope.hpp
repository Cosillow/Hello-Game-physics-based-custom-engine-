#include <vector>

#include "2dphysics.hpp"

using links = std::vector<Body>;

class Rope: UpdateableI
{
public:
    Rope(): UpdateableI() {}
    Rope(int numLinks, const Vector2& position);
    static constexpr float RopeSize = 3.0f;

    const links& getLinks() const { return this->_links; }

    void setPosition(const Vector2& pos) { this->_position = pos; }

    virtual void update(float deltaTime);
private:
    void applyConstraints();    
    links _links;
    Vector2 _position;
    
};
