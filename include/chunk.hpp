#pragma once

#include <unordered_map>
#include "2dphysics.hpp"
#include "platform.hpp"

#include "json.hpp"
using json = nlohmann::json;

class Chunk
{
private:
    Vector2 _position;
    std::unordered_map<Vector2, Platform, Vector2Hash> _platforms;
public:
    Chunk(int worldSeed, Vector2 position);
    Chunk(): Chunk(0,Vector2()) {}
    ~Chunk() {}
    // mutators
    void addPlatform(const Platform& platform, const Vector2& position) { this->_platforms.emplace(position, platform); }
    void removePlatform(const Vector2& position) { this->_platforms.erase(position); }
    json serialize() const;
    static Chunk deserialize();
    // getters
    const Vector2& getPosition() const { return this->_position; }
    
};
