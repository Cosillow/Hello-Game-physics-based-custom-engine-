#pragma once

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "json.hpp"
#include "constants.hpp"

using json = nlohmann::json;

class MapManager {
private:
    std::string _mapPath;
    std::vector<std::vector<int>> _loadedMap;
    int _tileSize;
    int _buffer;

public:
    MapManager(const std::string& mapPath, int tileSize, int buffer) :
        _mapPath(mapPath), _tileSize(tileSize), _buffer(buffer) {}

    bool loadMap() {
        std::ifstream file(_mapPath);
        if (!file.is_open()) {
            std::cerr << "Failed to open map file: " << _mapPath << std::endl;
            return false;
        }

        json mapData;
        file >> mapData;

        if (!mapData.is_array()) {
            std::cerr << "Invalid map file format: " << _mapPath << std::endl;
            return false;
        }

        this->_loadedMap.clear();

        for (const auto& row : mapData) {
            if (!row.is_array()) {
                std::cerr << "Invalid map row format: " << _mapPath << std::endl;
                this->_loadedMap.clear();
                return false;
            }

            std::vector<int> mapRow;
            for (const auto& tile : row) {
                if (!tile.is_number_integer()) {
                    std::cerr << "Invalid map tile format: " << _mapPath << std::endl;
                    this->_loadedMap.clear();
                    return false;
                }

                mapRow.push_back(tile);
            }

            this->_loadedMap.push_back(mapRow);
        }

        return true;
    }

    void unloadMap() {
        this->_loadedMap.clear();
    }

    // void renderMap(SDL_Renderer* renderer, int offsetX, int offsetY) {
    //     if (this->_loadedMap.empty())
    //         return;

    //     int startX = std::max(0, offsetX / this->_tileSize - this->_buffer);
    //     int startY = std::max(0, offsetY / this->_tileSize - this->_buffer);
    //     int endX = std::min(static_cast<int>( this->_loadedMap[0].size() ), static_cast<int>( (offsetX + Constants::WINDOW_WIDTH) / this->_tileSize + this->_buffer ));
    //     int endY = std::min(static_cast<int>( this->_loadedMap.size() ), static_cast<int>( (offsetY + Constants::WINDOW_HEIGHT) / this->_tileSize + this->_buffer ));

    //     for (int y = startY; y < endY; ++y) {
    //         for (int x = startX; x < endX; ++x) {
    //             int tile = this->_loadedMap[y][x];
    //             // Render the tile using the tile index and the appropriate texture
    //             // ...
    //         }
    //     }
    // }
};
