#pragma once

#include <SDL2/SDL.h>
#include "2dphysics.hpp"


class Sprite {
protected:
    SDL_Texture* _spriteSheet;
    SDL_Rect _box;
    bool _mirrorX;
    bool _mirrorY;

public:
    Sprite() : _spriteSheet(nullptr), _box({0, 0, 0, 0}) {}

    Sprite(SDL_Texture* spritesheet, int x, int y, int width, int height): 
    _spriteSheet(spritesheet), 
    _box({x, y, width, height}),
    _mirrorX(false),
    _mirrorY(false) {}
    Sprite(SDL_Texture* sprite): // constructor for single sprite, assumes (x,y) as canvas
    _spriteSheet(sprite), 
    _box({0,0,0,0}),
    _mirrorX(false),
    _mirrorY(false) { this->setSpritesheet(sprite); }
    ~Sprite() {/*ResourceManager is in charge of the texture*/}

    // getters
    bool getMirrorX() const { return this->_mirrorX; }
    bool getMirrorY() const { return this->_mirrorY; }
    const SDL_Rect& getRect() const { return this->_box; }
    SDL_Texture* getSpritesheet() const { return this->_spriteSheet; }

    // setters
    void setMirrorX(bool mirror) { this->_mirrorX = mirror; }
    void setMirrorY(bool mirror) { this->_mirrorY = mirror; }
    void setSpritesheet(SDL_Texture* spritesheet, int x, int y, int width, int height)
    {
        this->_spriteSheet = spritesheet;
        this->_box.x = x;
        this->_box.y = y;
        this->_box.w = width;
        this->_box.h = height;
    }
    void setSpritesheet(SDL_Texture* spritesheet)
    {
        this->_spriteSheet = spritesheet;
        SDL_QueryTexture(spritesheet, nullptr, nullptr, &_box.w, &_box.h);
    }
    void setFrame(int x, int y)
    {
        this->_box.x = x;
        this->_box.y = y;
    }
};

class SpriteContainer {
protected:
    Sprite _sprite;
public:
    SpriteContainer(): _sprite(Sprite()) {};
    SpriteContainer(const Sprite& sprite): _sprite(sprite) {};
    ~SpriteContainer() {};
    const Sprite& getSprite() const { return this->_sprite; };
};
