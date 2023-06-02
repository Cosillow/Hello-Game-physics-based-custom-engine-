// #include <SDL2/SDL.h>
// #include "2dphysics.hpp"

// class Sprite {
// private:
//     SDL_Texture& _texture;
//     Vector2 _size;

// public:
//     Sprite() : _texture(nullptr), width(0), height(0) {}

//     Sprite(SDL_Texture* texture, int width, int height)
//         : _texture(texture), width(width), height(height) {}

//     void setTexture(SDL_Texture* texture, int width, int height) {
//         this->_texture = texture;
//         this->width = width;
//         this->height = height;
//     }

//     void render(SDL_Renderer& renderer, int x, int y) const {
//         SDL_Rect destRect{x, y, width, height};
//         SDL_RenderCopy(&renderer, texture, nullptr, &destRect);
//     }
// };