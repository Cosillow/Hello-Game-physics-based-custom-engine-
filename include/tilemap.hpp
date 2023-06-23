#pragma once

#include <unordered_map>
#include <vector>
#include <utility>
#include "platform.hpp"
#include "2dphysics.hpp"
#include "chunk.hpp"

class TileMap
{
private:
    int _loadRadius; // minimum: 2 (to get a 5x5 grid)
    int _worldSeed;
    std::vector<std::vector<Chunk>> _loadedChunks;
    const std::string FILE_NAME = "./res./map-file.json";
public:
    TileMap(int worldSeed, int renderRadius): _loadRadius(renderRadius), _worldSeed(worldSeed), _loadedChunks() {}
    TileMap(int worldSeed): TileMap(worldSeed, 2) {}
    TileMap(): TileMap(0) {}
    ~TileMap() {}
    // mutators
    void loadChunk(Vector2 chunkPosition);
    void unloadChunk(Vector2 chunkPosition);
    void setLoadRadius(int loadRadius) { _loadRadius = loadRadius; }
    // getters
    int getLoadRadius() const { return _loadRadius; }
private:
    Vector2 getChunkCoordinates(const Vector2& position) const;
    bool loadChunkFromFile(Vector2 chunkPosition) const;
    bool saveChunkToFile(const Chunk& chunk) const;
};
