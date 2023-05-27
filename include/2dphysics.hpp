#pragma once

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

struct UpdateableI {
    UpdateableI() {}
    ~UpdateableI() {}
    virtual void update(float deltaTime) = 0;
};

// ********************************************************************************************************
// VECTOR2

struct Vector2 {
    float x;
    float y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float a_x, float a_y) : x(a_x), y(a_y) {}
    ~Vector2() {}

    SDL_Point getSDLPoint() const {
        SDL_Point point;
        point.x = static_cast<int>(x);
        point.y = static_cast<int>(y);
        return point;
    }

    float calculateAngle(const Vector2& to) const {
        return std::atan2(to.y - this->y, to.x - this->x);
    }

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    Vector2 operator*(Vector2 other) const {
        return Vector2(this->x * other.x, y * other.y);
    }

    Vector2 operator/(float scalar) const {
        if (scalar != 0.0f) {
            float invScalar = 1.0f / scalar;
            return Vector2(x * invScalar, y * invScalar);
        }
        // Handle division by zero gracefully (return a zero vector)
        return Vector2();
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(float scalar) {
        if (scalar != 0.0f) {
            float invScalar = 1.0f / scalar;
            x *= invScalar;
            y *= invScalar;
        }
        // Handle division by zero gracefully (do nothing)
        return *this;
    }

    float dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2 normalize() const {
        float mag = magnitude();
        if (mag != 0.0f) {
            float invMag = 1.0f / mag;
            return Vector2(x * invMag, y * invMag);
        }
        // Handle zero vector gracefully (return a zero vector)
        return Vector2();
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}
};

// ********************************************************************************************************
// Hitbox

struct Hitbox
{
    enum class Type {
        Circle,
        BoundingBox
    };

    Vector2 _offset;
    Vector2 _center;
    Vector2 _size;
    float _circleRadius;

    Hitbox(float offsetX, float offsetY, float height, float width): 
    _offset({offsetX, offsetY}), 
    _center({0,0}),
    _size({width, height}),
    _circleRadius(0) {/* create bounding box */}
    Hitbox(float offsetX, float offsetY, float radius):  
    _offset({offsetX, offsetY}), 
    _center({0,0}),
    _size({0, 0}),
    _circleRadius(radius) {/* create circle */} 

    Type getType() const {
        if (this->_circleRadius) return Type::Circle;
        else return Type::BoundingBox; 
    }

    void setCenter(Vector2& center) { _center = center; }

    bool checkCollisions(const Hitbox& other) const {
        if (this->getType() == Hitbox::Type::Circle && other.getType() == Hitbox::Type::Circle)
        {
            float distance = (this->_center - other._center).magnitude();

            return distance < (this->_size.x + other._size.x) / 2;
        } else if (this->getType() == Type::BoundingBox && other.getType() == Type::BoundingBox)
        {
            Vector2 topLeft = this->_center - this->_size / 2;
            Vector2 otherTopLeft = other._center - other._size / 2;

            return (topLeft.x < otherTopLeft.x + other._size.x) &&
                   (topLeft.x + this->_size.x > otherTopLeft.x) &&
                   (topLeft.y < otherTopLeft.y + other._size.y) &&
                   (topLeft.y + this->_size.y > otherTopLeft.y);
        }
    }

    float getLeftX() {
        if (this->getType() == Type::Circle)
        {
            return _center.x - _circleRadius;
        } else {
            return _center.x - this->_size.x;
        }
    }

    float getRightX() {
        if (this->getType() == Type::Circle)
        {
            return _center.x + _circleRadius;
        } else {
            return _center.x + this->_size.x;
        }
    }

    float getTopY() {
        if (this->getType() == Type::Circle)
        {
            return _center.y - _circleRadius;
        } else {
            return _center.y - this->_size.y;
        }
    }

    float getBottomY() {
        if (this->getType() == Type::Circle)
        {
            return _center.y + _circleRadius;
        } else {
            return _center.y + this->_size.y;
        }
    }
};

// ********************************************************************************************************
// BODY

class Body : public UpdateableI {
private:
    Vector2 _position;
    Vector2 _velocity;
    Vector2 _totalForce;
    float _mass;
    bool _isStatic;
    Hitbox* _hitbox;

public:
    
    Body(Vector2 a_position, float a_mass, bool a_isStatic = false): UpdateableI(),
    _position(a_position), 
    _velocity(Vector2()), 
    _totalForce(Vector2()),
    _mass(a_mass),
    _isStatic(a_isStatic),
    _hitbox(nullptr) {}

    Body(float _mass, bool a_isStatic = false): UpdateableI(),
    _position({0,0}), 
    _velocity(Vector2()), 
    _totalForce(Vector2()),
    _mass(_mass),
    _isStatic(a_isStatic),
    _hitbox(nullptr) {}

    ~Body() { this->cleanup(); }
    void cleanup() {
        if (_hitbox) delete _hitbox;
    }

    void addHitboxBB(float offsetX, float offsetY, float height, float width) {
        this->cleanup();
        this->_hitbox = new Hitbox(offsetX, offsetY, height, width);
    }
    void addHitboxBB(float height, float width) {
        this->cleanup();
        this->_hitbox = new Hitbox(0, 0, height, width);
    }
    void addHitboxCircle(float offsetX, float offsetY, float radius) {
        this->cleanup();
        this->_hitbox = new Hitbox(offsetX, offsetY, radius);
    }
    void applyForce(const Vector2& force) {
        if (!_isStatic) {
            _totalForce += force;
        }
    }
    virtual void update(float deltaTime) {
        if (!_isStatic) {
            Vector2 acceleration = _totalForce / _mass;
            _velocity += acceleration * deltaTime;
            _position += _velocity * deltaTime;

            // Reset the total force for the next update
            _totalForce = Vector2();

            // update hitbox
            if (this->_hitbox) this->_hitbox->setCenter(this->_position);
        }
    }
    void applyImpulse(const Vector2 impulse) {
        if (!_isStatic) {
            _velocity += impulse / _mass;
        }
    }

    // getters
    Hitbox* getHitbox() const { return _hitbox; }
    Vector2 getPosition() const {
        return _position;
    }
    Vector2 getVelocity() const {
        return _velocity;
    }
    Vector2 getAcceleration() const {
        if (!_isStatic) {
            return _totalForce / _mass;
        }
        // If the body is static, return a zero acceleration
        return Vector2();
    }
    bool isStaticBody() const {
        return _isStatic;
    }
    // setters
   void setVelocity(const Vector2& velocity) {
        if (!_isStatic) {
            _velocity = velocity;
        }
    }
    float getMass() const {
        return _mass;
    }
    void setMass(float mass) {
        _mass = mass;
    }
    void setStatic(bool isStatic) {
        _isStatic = isStatic;
    }
    void setPosition(const Vector2& position) {
        _position = position;
    }


    

    

    friend std::ostream& operator<<(std::ostream& os, const Body& body) {
        if (body.isStaticBody()) os << "STATIC _position: " << body.getPosition() << ", _mass: " << body.getMass();
        else os << "_position: " << body.getPosition() << ", _velocity: " << body.getVelocity() << 
        ", Acceleration: " << body.getAcceleration() << ", _mass: " << body.getMass();
        return os;
    }
};



