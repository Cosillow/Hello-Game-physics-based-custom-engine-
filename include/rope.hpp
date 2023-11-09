#include <vector>

#include "2dphysics.hpp"

using segments = std::vector<Body>;

class Rope: UpdateableI
{
public:
    Rope(): UpdateableI() {}
    Rope(int numLinks, const Vector2& position);
    static constexpr float RopeSize = 10.0f;

    const segments& getSegments() const { return this->_links; }

    void setPosition(const Vector2& pos) { this->_position = pos; }

    virtual void update(float deltaTime);

private:
    void applyConstraints();    
    segments _links;
    Vector2 _position;
    
    
};
