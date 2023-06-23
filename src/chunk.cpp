#include "chunk.hpp"

#include "json.hpp"
using json = nlohmann::json;

Chunk::Chunk(int worldSeed, Vector2 position): 
_position(position), 
_platforms() 
{
    // generate a chunk based on worldSeed (combo943879328) position
}
