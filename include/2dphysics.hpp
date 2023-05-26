#pragma once

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

// ********************************************************************************************************
// VECTOR2

struct Vector2 {
    float x;
    float y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float a_x, float a_y) : x(a_x), y(a_y) {}

    SDL_Point getSDLPoint() const {
        SDL_Point point;
        point.x = static_cast<int>(x);
        point.y = static_cast<int>(y);
        return point;
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
// BODY

class Body {
private:
    Vector2 position;
    Vector2 velocity;
    Vector2 totalForce;
    float mass;
    bool isStatic;

public:
    Body(Vector2 a_position, float a_mass, bool a_isStatic = false)
        : position(a_position), velocity(Vector2()), totalForce(Vector2()), mass(a_mass), isStatic(a_isStatic) {}

    void applyForce(const Vector2& force) {
        if (!isStatic) {
            totalForce += force;
        }
    }

    void update(float deltaTime) {
        if (!isStatic) {
            Vector2 acceleration = totalForce / mass;
            velocity += acceleration * deltaTime;
            position += velocity * deltaTime;

            // Reset the total force for the next update
            totalForce = Vector2();
        }
    }

    Vector2 getPosition() const {
        return position;
    }

    void setPosition(const Vector2& _position) {
        position = _position;
    }

    Vector2 getVelocity() const {
        return velocity;
    }

   void setVelocity(const Vector2& _velocity) {
        if (!isStatic) {
            velocity = _velocity;
        }
    }

    float getMass() const {
        return mass;
    }

    void setMass(float _mass) {
        mass = _mass;
    }

    Vector2 getAcceleration() const {
        if (!isStatic) {
            return totalForce / mass;
        }
        // If the body is static, return a zero acceleration
        return Vector2();
    }

    bool isStaticBody() const {
        return isStatic;
    }

    void setStatic(bool _isStatic) {
        isStatic = _isStatic;
    }

    friend std::ostream& operator<<(std::ostream& os, const Body& body) {
        if (body.isStaticBody()) os << "STATIC Position: " << body.getPosition() << ", Mass: " << body.getMass();
        else os << "Position: " << body.getPosition() << ", Velocity: " << body.getVelocity() << 
        ", Acceleration: " << body.getAcceleration() << ", Mass: " << body.getMass();
        return os;
    }
};



