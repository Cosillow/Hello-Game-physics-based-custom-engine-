#pragma once

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include "constants.hpp"

struct UpdateableI
{
    UpdateableI() {}
    virtual ~UpdateableI() {}
    virtual void update(float deltaTime) = 0;
};

struct Vector2
{
    float x;
    float y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float a_x, float a_y) : x(a_x), y(a_y) {}
    virtual ~Vector2() {}

    SDL_Point getSDLPoint() const
    {
        SDL_Point point;
        point.x = static_cast<int>(this->x);
        point.y = static_cast<int>(this->y);
        return point;
    }

    float distance(const Vector2 &other) const
    {
        Vector2 d = other - *this;
        return std::sqrt((d.x * d.x) + (d.y * d.y));
    }

    float calculateAngle(const Vector2 &to) const
    {
        return std::atan2(to.y - this->y, to.x - this->x);
    }

    Vector2 operator+(const Vector2 &other) const
    {
        return Vector2(this->x + other.x, this->y + other.y);
    }

    Vector2 operator-(const Vector2 &other) const
    {
        return Vector2(this->x - other.x, this->y - other.y);
    }

    Vector2 operator*(float scalar) const
    {
        return Vector2(this->x * scalar, this->y * scalar);
    }

    Vector2 operator/(float scalar) const
    {
        if (scalar == 0.0f)
            return Vector2();
        float invScalar = 1.0f / scalar;
        return Vector2(this->x * invScalar, this->y * invScalar);
    }

    friend bool operator==(const Vector2 &lhs, const Vector2 &rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    friend bool operator!=(const Vector2 &lhs, const Vector2 &rhs)
    {
        return !(lhs == rhs);
    }

    Vector2 &operator+=(const Vector2 &other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vector2 &operator-=(const Vector2 &other)
    {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }

    Vector2 &operator*=(float scalar)
    {
        this->x *= scalar;
        this->y *= scalar;
        return *this;
    }

    Vector2 &operator/=(float scalar)
    {
        if (scalar == 0.0f)
            return *this;
        float invScalar = 1.0f / scalar;
        this->x *= invScalar;
        this->y *= invScalar;
    }

    friend bool operator<(const Vector2 &lhs, const Vector2 &rhs)
    {
        return lhs.magnitude() < rhs.magnitude();
    }

    friend bool operator>(const Vector2 &lhs, const Vector2 &rhs)
    {
        return lhs.magnitude() > rhs.magnitude();
    }

    float dot(const Vector2 &other) const
    {
        return this->x * other.x + this->y * other.y;
    }

    float magnitude() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vector2 normalize() const
    {
        float mag = this->magnitude();
        if (mag == 0.0f)
            return Vector2();
        float invMag = 1.0f / mag;
        return Vector2(x * invMag, y * invMag);
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector2 &vec)
    {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};

struct Vector2Hash
{
    std::size_t operator()(const Vector2 &v) const
    {
        std::size_t h1 = std::hash<float>{}(v.x);
        std::size_t h2 = std::hash<float>{}(v.y);
        return h1 ^ (h2 << 1);
    }
};

struct Hitbox
{
    enum class Type
    {
        Circle,
        BoundingBox
    };

    Vector2 _offset;
    Vector2 _center;
    Vector2 _size;
    float _circleRadius;
    bool _inCollision;

    Hitbox(float offsetX, float offsetY, float width, float height) : 
    _offset({offsetX, offsetY}),
    _center({0, 0}),
    _size({width, height}),
    _circleRadius(0),
    _inCollision(0)
    { /* create bounding box */ }

    Hitbox(float offsetX, float offsetY, float radius) : 
    _offset({offsetX, offsetY}),
    _center({0, 0}),
    _size({0, 0}),
    _circleRadius(radius),
    _inCollision(0)
    { /* create circle */ }

    Hitbox() : Hitbox(0, 0, 0, 0)
    { /* create a default bounding box */ }
    ~Hitbox(){};

    Type getType() const
    {
        if (this->_circleRadius)
            return Type::Circle;
        else
            return Type::BoundingBox;
    }

    void setCenter(Vector2 &center) { this->_center = center; }
    void setCollision(bool col) { this->_inCollision = col; }

    bool checkCollisions(const Hitbox &other) const
    {
        if (this->getType() == Hitbox::Type::Circle && other.getType() == Hitbox::Type::Circle)
        {
            // optimized without the sqrt function
            float r = this->_circleRadius + other._circleRadius;
            r *= r;
            return r < std::pow(this->_center.x + other._center.x, 2) + std::pow(this->_center.y + other._center.y, 2);
        }
        else if (this->getType() == Type::BoundingBox && other.getType() == Type::BoundingBox)
        {
            Vector2 topLeft = this->_center - this->_size / 2;
            Vector2 otherTopLeft = other._center - other._size / 2;

            return (topLeft.x < otherTopLeft.x + other._size.x) &&
                   (topLeft.x + this->_size.x > otherTopLeft.x) &&
                   (topLeft.y < otherTopLeft.y + other._size.y) &&
                   (topLeft.y + this->_size.y > otherTopLeft.y);
        }
        return false;
    }

    float getLeftX() const
    {
        if (this->getType() == Type::Circle)
        {
            return this->_center.x - this->_circleRadius;
        }
        else
        {
            return this->_center.x - (this->_size.x / 2);
        }
    }

    float getRightX() const
    {
        if (this->getType() == Type::Circle)
        {
            return this->_center.x + this->_circleRadius;
        }
        else
        {
            return this->_center.x + (this->_size.x / 2);
        }
    }

    float getTopY() const
    {
        if (this->getType() == Type::Circle)
        {
            return this->_center.y - this->_circleRadius;
        }
        else
        {
            return this->_center.y - (this->_size.y / 2);
        }
    }

    float getBottomY() const
    {
        if (this->getType() == Type::Circle)
        {
            return this->_center.y + this->_circleRadius;
        }
        else
        {
            return this->_center.y + (this->_size.y / 2);
        }
    }

    SDL_Rect &getSDLRect() const
    {
        static SDL_Rect rect;
        rect.x = static_cast<int>(_center.x - (_size.x / 2));
        rect.y = static_cast<int>(_center.y - (_size.y / 2));
        rect.w = static_cast<int>(_size.x);
        rect.h = static_cast<int>(_size.y);
        return rect;
    }
};

class Body : public UpdateableI
{
private:
    Vector2 _position;
    Vector2 _oldPosition;
    Vector2 _acceleration;
    bool _isStatic;
    Hitbox *_hitbox;
    bool _isTouchingGround;

public:
    Body(Vector2 position, bool a_isStatic = false) : 
    UpdateableI()
    , _position(position)
    , _oldPosition(position)
    , _acceleration(Vector2())
    , _isStatic(a_isStatic)
    , _hitbox(nullptr)
    , _isTouchingGround(false) {}

    Body(bool isStatic) : Body({0, 0}, isStatic) {}
    Body() : Body(0.0) {}

    virtual ~Body() { this->cleanup(); }
    void cleanup()
    {
        if (this->_hitbox)
            delete this->_hitbox;
    }

    void addHitboxBB(float offsetX, float offsetY, float width, float height)
    {
        this->cleanup();
        this->_hitbox = new Hitbox(offsetX, offsetY, width, height);
        this->_hitbox->setCenter(this->_position);
    }
    void addHitboxBB(float width, float height)
    {
        this->addHitboxBB(0, 0, width, height);
    }
    void addHitboxCircle(float offsetX, float offsetY, float radius)
    {
        this->cleanup();
        this->_hitbox = new Hitbox(offsetX, offsetY, radius);
        this->_hitbox->setCenter(this->_position);
    }
    void applyForce(const Vector2 &force)
    {
        if (this->_isStatic)
            return;
        this->_acceleration += force;
    }
    virtual void update(float deltaTime)
    {
        if (this->_isStatic)
            return;

        Vector2 finalAcceleration = this->getAcceleration();
        Vector2 velocity = this->getVelocity();

        if (this->_isTouchingGround && this->_acceleration.x == 0)
        {
            // body is stopping
            // apply friction (stop instantly)
            this->_oldPosition = this->_position;
        }
        else
        {
            // body is moving
            Vector2 newPosition = (this->_position * 2.0f) - this->_oldPosition + (finalAcceleration * (deltaTime * deltaTime));
            this->_oldPosition = this->_position;
            this->_position = newPosition;
        }

        // Update hitbox
        if (this->_hitbox)
            this->_hitbox->setCenter(this->_position);

        // reset and allow collisions manager to set true
        this->setIsTouchingGround(false);
    }
    void applyImpulse(const Vector2 impulse)
    {
        if (this->_isStatic)
            return;
        this->setVelocity(getVelocity() + impulse);
    }

    // getters
    Hitbox *getHitbox() const { return this->_hitbox; }
    const Vector2 getPosition() const
    {
        return this->_position;
    }
    const Vector2 getOldPosition() const
    {
        return this->_oldPosition;
    }
    Vector2 getVelocity() const
    {
        return this->_position - this->_oldPosition;
    }
    const Vector2 getAcceleration() const
    {
        return (this->_acceleration + Vector2(0, Constants::GRAVITY));
    }
    bool isStaticBody() const
    {
        return this->_isStatic;
    }
    bool isTouchingGround() const
    {
        return this->_isTouchingGround;
    }
    // setters
    void setStatic(bool isStatic)
    {
        this->_isStatic = isStatic;
    }
    void setIsTouchingGround(bool isTouchingGround)
    {
        this->_isTouchingGround = isTouchingGround;
        if (this->_hitbox)
            this->_hitbox->setCollision(isTouchingGround);
    }
    void setVelocity(const Vector2 &velocity)
    {
        if (this->_isStatic)
            return;
        this->_oldPosition = this->_position - velocity;
        this->_position = this->_oldPosition + velocity;
    }

    virtual void setPosition(const Vector2 &position)
    {
        this->_position = position;
    }
    void setOldPosition(const Vector2 &position)
    {
        this->_oldPosition = position;
    }

    friend std::ostream &operator<<(std::ostream &os, const Body &body)
    {
        if (body.isStaticBody())
            os << "STATIC Position: " << body.getPosition();
        else
            os << "Position: " << body.getPosition() << ", Velocity: " << body.getVelocity() << ", Acceleration: " << body.getAcceleration();
        return os;
    }
};
