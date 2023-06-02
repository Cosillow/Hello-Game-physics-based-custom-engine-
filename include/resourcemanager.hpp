#include <iostream>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class ResourceManager {
private:
    std::unordered_map<std::string, SDL_Texture*> textures;

    bool loadTexture(SDL_Renderer& renderer, const std::string& name, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load texture: " << filePath << ", " << IMG_GetError() << std::endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        return false;
    }

    textures[name] = texture;
    return true;
}

    std::string getFileNameWithoutExtension(const std::string& filePath) const {
        size_t lastSlash = filePath.find_last_of("/\\");
        size_t lastDot = filePath.find_last_of(".");
        if (lastDot == std::string::npos || lastDot < lastSlash) {
            // No extension found or dot is before the last slash (in a directory path)
            return filePath.substr(lastSlash + 1);
        }

        return filePath.substr(lastSlash + 1, lastDot - lastSlash - 1);
    }

public:
    ResourceManager(SDL_Renderer& renderer, const std::vector<std::string>& texturePaths) {
        for (const auto& path : texturePaths) {
            // strip the path to the file name and file path
            const std::string& name = this->getFileNameWithoutExtension(path);
            std::cout << "name: " << name << " path: "<< path << std::endl;
            const bool texLoaded = this->loadTexture(renderer, name, path);
            if (!texLoaded) textures[name] = nullptr;
        }
    }

    ~ResourceManager() {
        for (auto& pair : textures) {
            SDL_DestroyTexture(pair.second);
        }
    }    

    // std::vector<std::string> getTextureNames() const {
    //     std::vector<std::string> names;
    //     names.reserve(textures.size());

    //     for (const auto& pair : textures) {
    //         names.push_back(pair.first);
    //     }

    //     return names;
    // }

    SDL_Texture* getTexture(const std::string& name) const {
        auto it = textures.find(name);
        if (it == textures.end()) {
            std::cerr << "Texture not found: " << name << std::endl;
            return nullptr;
        }

        return it->second;
    }
};
