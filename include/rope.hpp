#include <vector>
#include <memory>

#include "2dphysics.hpp"

using segments = std::vector<std::shared_ptr<Body>>;

class Rope: UpdateableI
{
public:
    Rope(): UpdateableI() {}
    Rope(int numLinks, const Vector2& position);
    static constexpr float RopeSize = 1.0f;

    const segments& getSegments() const { return this->_links; }

    void setPosition(const Vector2& pos) { this->_position = pos; }

    float getSize() { return this->_links[0]->getPosition().distance(this->_links[this->_links.size()-1]->getPosition()); }

    virtual void update(float deltaTime);

private:
    void applyConstraints();    
    segments _links;
    Vector2 _position;
    
    
};
