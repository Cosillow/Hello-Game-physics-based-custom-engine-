#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string.h>

#include "texture.hpp"

Texture::Texture(SDL_Renderer *renderer, const std::string &file)
{
    SDL_Surface *surface = IMG_Load(file.c_str());
    if (!surface)
    {
        std::cerr << "Failed to load image: " << file << " SDL_image Error: " << IMG_GetError() << std::endl;
        _texture = nullptr;
    }
    else
    {
        _texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!_texture)
        {
            std::cerr << "Failed to create texture from surface. SDL Error: " << SDL_GetError() << std::endl;
        }

        // We no longer need the surface after texture is created
        SDL_FreeSurface(surface);
    }
}

Texture::~Texture()
{
    // SDL_DestroyTexture can safely be called on nullptr, so no need to check for it here
    SDL_DestroyTexture(_texture);
}