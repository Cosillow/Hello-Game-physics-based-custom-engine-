#pragma once

#include <iostream>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class ResourceManager
{
private:
    std::unordered_map<std::string, SDL_Texture*> textures;
    SDL_Renderer* renderer;

    ResourceManager() : renderer(nullptr) {}

    ~ResourceManager()
    {
        for (auto &pair : textures)
        {
            SDL_DestroyTexture(pair.second);
        }
    }

    std::string getFileNameWithoutExtension(const std::string &filePath) const
    {
        size_t lastSlash = filePath.find_last_of("/\\");
        size_t lastDot = filePath.find_last_of(".");
        if (lastDot == std::string::npos || lastDot < lastSlash)
        {
            // No extension found or dot is before the last slash (in a directory path)
            return filePath.substr(lastSlash + 1);
        }

        return filePath.substr(lastSlash + 1, lastDot - lastSlash - 1);
    }
public:
    static SDL_Texture* openTexture(const std::string &path)
    {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface)
        {
            std::cerr << "Failed to load texture: " << path << ", " << IMG_GetError() << std::endl;
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(getInstance().renderer, surface);
        SDL_FreeSurface(surface);
        if (!texture)
        {
            std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        return texture;
    }

    static ResourceManager &getInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    static void initialize(SDL_Renderer *renderer, const std::vector<std::string> &texturePaths)
    {
        ResourceManager &instance = getInstance();
        instance.renderer = renderer;

        for (const auto &path : texturePaths)
        {
            const std::string &name = instance.getFileNameWithoutExtension(path);
            std::cout << "name: " << name << " path: " << path << std::endl;
            SDL_Texture* texture = ResourceManager::openTexture(path);

            instance.textures[name] = texture;
        }
    }

    SDL_Texture* getTexture(const std::string &name) const
    {
        auto it = textures.find(name);
        if (it == textures.end())
        {
            std::cerr << "Texture not found: " << name << std::endl;
            return nullptr;
        }

        return it->second;
    }
};
