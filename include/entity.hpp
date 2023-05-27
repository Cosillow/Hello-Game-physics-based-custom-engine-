// #pragma once
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <vector>
// #include <memory>
// #include <unordered_map>
// #include "texture.hpp"
// #include "2dphysics.hpp"

// class Body
// {
// public:
//     enum class ForceType
//     {
//         Gravity,
//         Jump
//     };

    
//     Body(Vector2 pos);
//     Body() { Body({0,0}); }
//     virtual ~Body() {}
//     const Vector2& getPosition() const { return _position; }
//     float getMass() const { return _mass; }
//     Vector2 getVelocity() const { return _velocity; }
//     void addForce(ForceType forceType);
//     void removeForce(ForceType forceType);
//     void applyImpulse(const Vector2& impulse);
//     virtual void setPosition(const Vector2& pos) { _position = pos; }
//     void setVelocity(const Vector2& vel) { _velocity = vel; }
//     void setAcceleration(const Vector2& acc) { _acceleration = acc; }
//     Vector2 getBoundingBoxCenter() const;

//     const SDL_Rect getBoundingBox() const;
//     virtual void update(float deltaTime);
// private:
//     using ForcesMap = std::unordered_map<ForceType, Vector2>;
//     ForcesMap _forces;
//     Vector2 _position;
//     Vector2 _acceleration;
//     Vector2 _velocity;
//     float _mass;
//     Vector2 _size;
// };
