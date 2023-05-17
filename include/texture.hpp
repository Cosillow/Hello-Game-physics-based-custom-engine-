#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>


class Texture
{
public:
    Texture(SDL_Renderer* renderer, const std::string& file);
    ~Texture() { SDL_DestroyTexture(_texture); }


    SDL_Texture* get() const { return _texture; }

private:
    SDL_Texture* _texture;

    // remove assignement and operator=
    Texture(const Texture&);
    Texture& operator=(const Texture&);
};