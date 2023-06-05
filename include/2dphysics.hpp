#pragma once

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include "constants.hpp"

struct UpdateableI {
    UpdateableI() {}
    virtual ~UpdateableI() {}
    virtual void update(float deltaTime) = 0;
};

// ********************************************************************************************************
// VECTOR2

struct Vector2 {
    float x;
    float y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float a_x, float a_y) : x(a_x), y(a_y) {}
    virtual ~Vector2() {}

    SDL_Point getSDLPoint() const {
        SDL_Point point;
        point.x = static_cast<int>(this->x);
        point.y = static_cast<int>(this->y);
        return point;
    }

    float distance(const Vector2& other) const {
        Vector2 d = other - *this;
        return std::sqrt((d.x * d.x) + (d.y * d.y));
    }

    float calculateAngle(const Vector2& to) const {
        return std::atan2(to.y - this->y, to.x - this->x);
    }

    Vector2 operator+(const Vector2& other) const {
        return Vector2(this->x + other.x, this->y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(this->x - other.x, this->y - other.y);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(this->x * scalar, this->y * scalar);
    }

    // Vector2 operator*(Vector2 other) const {
    //     return Vector2(this->x * other.x, this->y * other.y);
    // }

    Vector2 operator/(float scalar) const {
        if (scalar != 0.0f) {
            float invScalar = 1.0f / scalar;
            return Vector2(this->x * invScalar, this->y * invScalar);
        }
        // Handle division by zero gracefully (return a zero vector)
        return Vector2();
    }

    Vector2& operator+=(const Vector2& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    Vector2& operator*=(float scalar) {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    Vector2& operator/=(float scalar) {
        if (scalar != 0.0f) {
            float invScalar = 1.0f / scalar;
            this->x *= invScalar;
            this->y *= invScalar;
        }
        // Handle division by zero gracefully (do nothing)
        return *this;
    }

    friend bool operator<(const Vector2& lhs, const Vector2& rhs) {
        return lhs.magnitude() < rhs.magnitude();
    }

    friend bool operator>(const Vector2& lhs, const Vector2& rhs) {
        return lhs.magnitude() > rhs.magnitude();
    }


    float dot(const Vector2& other) const {
        return this->x * other.x + this->y * other.y;
    }

    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2 normalize() const {
        float mag = this->magnitude();
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

    Hitbox(float offsetX, float offsetY, float width, float height): 
    _offset({offsetX, offsetY}), 
    _center({0,0}),
    _size({width, height}),
    _circleRadius(0) {/* create bounding box */}
    Hitbox(float offsetX, float offsetY, float radius):  
    _offset({offsetX, offsetY}), 
    _center({0,0}),
    _size({0, 0}),
    _circleRadius(radius) {/* create circle */} 

    ~Hitbox() {};

    Type getType() const {
        if (this->_circleRadius) return Type::Circle;
        else return Type::BoundingBox; 
    }

    void setCenter(Vector2& center) { this->_center = center; }

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

    float getLeftX() const {
        if (this->getType() == Type::Circle)
        {
            return this->_center.x - this->_circleRadius;
        } else {
            return this->_center.x - (this->_size.x / 2);
        }
    }

    float getRightX() const {
        if (this->getType() == Type::Circle)
        {
            return this->_center.x + this->_circleRadius;
        } else {
            return this->_center.x + (this->_size.x / 2);
        }
    }

    float getTopY() const {
        if (this->getType() == Type::Circle)
        {
            return this->_center.y - this->_circleRadius;
        } else {
            return this->_center.y - (this->_size.y / 2);
        }
    }

    float getBottomY() const {
        if (this->getType() == Type::Circle)
        {
            return this->_center.y + this->_circleRadius;
        } else {
            return this->_center.y + (this->_size.y / 2);
        }
    }

    SDL_Rect& getSDLRect() const
    {
        static SDL_Rect rect;
        rect.x = static_cast<int>(_center.x - (_size.x / 2));
        rect.y = static_cast<int>(_center.y - (_size.y / 2));
        rect.w = static_cast<int>(_size.x);
        rect.h = static_cast<int>(_size.y);
        return rect;
    }
};

// ********************************************************************************************************
// BODY

class Body : public UpdateableI {
private:
    Vector2 _position;
    Vector2 _oldPosition;
    Vector2 _acceleration;
    bool _isStatic;
    Hitbox* _hitbox;
    bool _isTouchingGround;

    Vector2 applyFriction(Vector2 acceleration, float deltaTime) {
        Vector2 velocity = this->getVelocity();
        const float THRESHOLD = 0.1f;
        if (this->_isTouchingGround && std::abs(velocity.x) > THRESHOLD) {
            const float frictionForceX = velocity.x * Constants::PLAYER_FRICTION * -1;
            acceleration.x += frictionForceX;
        } else if (this->_isTouchingGround && this->_acceleration.x == 0 && std::abs(velocity.x) <= THRESHOLD) {
            return Vector2(0,0);
        }
        
        return acceleration;
    }


public:
    Body(Vector2 position, bool a_isStatic = false): UpdateableI(),
    _position(position),
    _oldPosition(position),
    _acceleration(Vector2()),
    _isStatic(a_isStatic),
    _hitbox(nullptr),
    _isTouchingGround(false) {}

    Body(bool isStatic): Body({0,0}, isStatic) { }
    Body(): Body(0.0) {}

    virtual ~Body() { this->cleanup(); }
    void cleanup() {
        if (this->_hitbox) delete this->_hitbox;
    }

    void addHitboxBB(float offsetX, float offsetY, float width, float height) {
        this->cleanup();
        this->_hitbox = new Hitbox(offsetX, offsetY, width, height);
    }
    void addHitboxBB(float width, float height) {
        this->cleanup();
        this->_hitbox = new Hitbox(0, 0, width, height);
    }
    void addHitboxCircle(float offsetX, float offsetY, float radius) {
        this->cleanup();
        this->_hitbox = new Hitbox(offsetX, offsetY, radius);
    }
    void applyForce(const Vector2& force) {
        if (!this->_isStatic) {
            this->_acceleration += force;
        }
    }
    virtual void update(float deltaTime) {
        if (!this->_isStatic) {
            const Vector2 finalAcceleration = this->applyFriction(this->getAcceleration(), deltaTime);
            Vector2 newPosition = (this->_position * 2.0f) - this->_oldPosition + (finalAcceleration * (deltaTime * deltaTime));
            
            this->_oldPosition = this->_position;
            this->_position = newPosition;

            // Update hitbox
            if (this->_hitbox) this->_hitbox->setCenter(this->_position);
        }
    }
    void applyImpulse(const Vector2 impulse) {
        if (!_isStatic) {
            Vector2 newVelocity = getVelocity() + impulse;

            std::cout << "applyImpulse() velocity: " << getVelocity() << " newVelocity: " << newVelocity << std::endl;

            // Update the position based on the average of old and new velocity
            Vector2 averageVelocity = (getVelocity() + newVelocity) * 0.5f;
            this->_position = this->_position + averageVelocity;

            // Update the old position based on the new velocity
            this->_oldPosition = this->_position - newVelocity;
        }
    }

    // getters
    Hitbox* getHitbox() const { return this->_hitbox; }
    const Vector2 getPosition() const {
        return this->_position;
    }
    const Vector2 getOldPosition() const {
        return this->_oldPosition;
    }
    Vector2 getVelocity() const {
        return this->_position - this->_oldPosition;
    }
    const Vector2 getAcceleration() const {
        return (this->_acceleration + Vector2(0, Constants::GRAVITY));
    }
    bool isStaticBody() const {
        return this->_isStatic;
    }
    bool isTouchingGround() const {
        return this->_isTouchingGround;
    }
    // setters
    void setStatic(bool isStatic) {
        this->_isStatic = isStatic;
    }
    void setIsTouchingGround(bool isTouchingGround) {
        this->_isTouchingGround = isTouchingGround;
    }
    void setPosition(const Vector2& position) {
        this->_position = position;
    } 
    void setOldPosition(const Vector2& position) {
        this->_oldPosition = position;
    }

    friend std::ostream& operator<<(std::ostream& os, const Body& body) {
        if (body.isStaticBody()) os << "STATIC Position: " << body.getPosition();
        else os << "Position: " << body.getPosition() << ", Velocity: " << body.getVelocity() << 
        ", Acceleration: " << body.getAcceleration();
        return os;
    }
};
