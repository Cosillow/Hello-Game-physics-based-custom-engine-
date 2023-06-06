#pragma once

#include <SDL2/SDL.h>
#include "2dphysics.hpp"


class Sprite {
private:
    SDL_Texture* _texture;
    SDL_Rect _box;
    bool _mirrorX;
    bool _mirrorY;

public:
    Sprite() : _texture(nullptr), _box({0, 0, 0, 0}) {}

    Sprite(SDL_Texture* texture, int x, int y, int width, int height): 
    _texture(texture), 
    _box({x, y, width, height}),
    _mirrorX(false),
    _mirrorY(false) {}
    Sprite(SDL_Texture* texture): 
    _texture(texture), 
    _box({0,0,0,0}),
    _mirrorX(false),
    _mirrorY(false) { this->setTexture(texture); }
    ~Sprite() {} // not in charge of the texture

    void setTexture(SDL_Texture* texture, int x, int y, int width, int height)
    {
        this->_texture = texture;
        this->_box.x = x;
        this->_box.y = y;
        this->_box.w = width;
        this->_box.h = height;
    }
    void setTexture(SDL_Texture* texture)
    {
        this->_texture = texture;
        SDL_QueryTexture(texture, nullptr, nullptr, &_box.w, &_box.h);
    }
    SDL_Texture* getTexture() const
    {
        return this->_texture;
    }

    const SDL_Rect& getRect() const
    {
        return this->_box;
    }

    void setMirrorX(bool mirror)
    {
        this->_mirrorX = mirror;
    }

    bool getMirrorX() const
    {
        return this->_mirrorX;
    }

    void setMirrorY(bool mirror)
    {
        this->_mirrorY = mirror;
    }

    bool getMirrorY() const
    {
        return this->_mirrorY;
    }
};

class SpriteContainer {
protected:
    Sprite _sprite;
public:
    SpriteContainer(): _sprite(Sprite()) {};
    SpriteContainer(const Sprite& sprite): _sprite(sprite) {};
    virtual ~SpriteContainer() {};
    const Sprite& getSprite() const { return this->_sprite; };
};

