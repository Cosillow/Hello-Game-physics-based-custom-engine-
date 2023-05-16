#include <SDL2/SDL.h>
#include <iostream>
#include <string.h>


class Texture
{
public:
    Texture(SDL_Renderer* renderer, const std::string& file);
    ~Texture();

    SDL_Texture* get() const { return _texture; }

    // Delete copy constructor and assignment operator to avoid shallow copies
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

private:
    SDL_Texture* _texture;
};