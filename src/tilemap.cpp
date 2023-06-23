#include "tilemap.hpp"
#include "constants.hpp"
#include "chunk.hpp"

#include "json.hpp"
using json = nlohmann::json;

Vector2 TileMap::getChunkCoordinates(const Vector2& position) const
{
    int chunkX = static_cast<int>(position.x) / Constants::CHUNK_SIZE;
    int chunkY = static_cast<int>(position.y) / Constants::CHUNK_SIZE;
    return Vector2(chunkX, chunkY);
}

void TileMap::loadChunk(Vector2 chunkPosition)
{
    if (this->_loadedChunks[chunkPosition.x][chunkPosition.y].getPosition() != chunkPosition)
    {
        // Chunk does not exist, generate a new one
        Chunk newChunk(_worldSeed, chunkPosition); // Pass the world seed to the Chunk constructor
        this->_loadedChunks[chunkPosition.x][chunkPosition.y] = std::move(newChunk);
    }
    else
    {
        // Chunk already exists, no need to generate
        loadChunkFromFile(chunkPosition);
    }
}

void TileMap::unloadChunk(Vector2 chunkPosition)
{
    if (!(this->_loadedChunks[chunkPosition.x][chunkPosition.y].getPosition() == chunkPosition)) return;
    // Unload or save the platforms within the chunk (implementation omitted)
    this->_loadedChunks[chunkPosition.x][chunkPosition.y] = Chunk(); // Replace with an empty chunk or nullify the data as per your requirements
}



bool TileMap::loadChunkFromFile(Vector2 chunkPosition) const
{
    SDL_RWops* file = SDL_RWFromFile(FILE_NAME.c_str(), "r");
    if (!file) return false;

    // Get the size of the file
    Sint64 fileSize = SDL_RWsize(file);

    // Allocate a buffer to hold the file data
    char* buffer = new char[fileSize + 1];

    // Read the file data into the buffer
    Sint64 bytesRead = SDL_RWread(file, buffer, 1, fileSize);
    buffer[bytesRead] = '\0'; // Null-terminate the buffer

    // Parse the JSON data
    json mapData = json::parse(buffer);

    delete[] buffer; // Clean up the buffer

    // Load chunk data from the JSON file
    std::string chunkKey = "Chunk_" + std::to_string(chunkPosition.x) + "_" + std::to_string(chunkPosition.y);

    if (!mapData.contains(chunkKey)) return false;

    // Get the serialized chunk data from the JSON map
    std::string serializedChunkStr = mapData[chunkKey];
    // Deserialize the chunk data
    Chunk loadedChunk;
    const char* serializedChunk = serializedChunkStr.data();
    size_t chunkSize = sizeof(Chunk);
    std::memcpy(&loadedChunk, serializedChunk, chunkSize);
   
    // TODO: do something with the loadedChunk
    return true;
}

bool TileMap::saveChunkToFile(const Chunk& chunk) const
{
    SDL_RWops* file = SDL_RWFromFile(FILE_NAME.c_str(), "r+");
    if (!file) return false;

    json mapData;
    
    // Get the size of the existing file
    Sint64 fileSize = SDL_RWsize(file);

    // Allocate a buffer to hold the file data
    char* buffer = new char[fileSize + 1];

    // Read the file data into the buffer
    Sint64 bytesRead = SDL_RWread(file, buffer, 1, fileSize);
    buffer[bytesRead] = '\0'; // Null-terminate the buffer

    // Parse the JSON data
    mapData = json::parse(buffer);

    delete[] buffer; // Clean up the buffer

    // Close the file
    SDL_RWclose(file);
    
    // Update the mapData with the chunk data
    // Modify the code below based on your chunk data structure
    std::string chunkKey = "Chunk_" + std::to_string(chunk.getPosition().x) + "_" + std::to_string(chunk.getPosition().y);


    // Serialize the chunk and store it as a binary string
    const char* serializedChunk = reinterpret_cast<const char*>(&chunk);
    size_t chunkSize = sizeof(chunk);
    std::string serializedChunkStr(serializedChunk, chunkSize);

    mapData[chunkKey] = serializedChunkStr;
  

    file = SDL_RWFromFile(FILE_NAME.c_str(), "w");
    if (!file) return false;

    // Write the updated mapData to the file
    std::string jsonData = mapData.dump(4);

    // Write the JSON data to the file
    Sint64 bytesWritten = SDL_RWwrite(file, jsonData.c_str(), 1, jsonData.size());

    // Close the file
    SDL_RWclose(file);

    return bytesWritten == jsonData.size();
}
