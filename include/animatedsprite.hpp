#pragma once
#include "sprite.hpp"
#include "2dphysics.hpp"

class AnimatedSprite : public Sprite, public UpdateableI
{
private:
    int _totalFrames;
    int _currentFrame;
    float _timeLeftUntilFrameChange;
public:
    AnimatedSprite(SDL_Texture* spritesheet, int width, int height, int x, int y, int totalFrames): Sprite(spritesheet, x, y, width, height),
        _totalFrames(totalFrames),
        _currentFrame(0),
        _timeLeftUntilFrameChange(Constants::FRAME_DURATION) {}
    AnimatedSprite(SDL_Texture* spritesheet, int width, int height, int totalFrames): AnimatedSprite(spritesheet, width, height, 0, 0, totalFrames) {}
    AnimatedSprite(): AnimatedSprite(nullptr, 0, 0, 0) {}

    void update(float deltaTime) override
    {
        _timeLeftUntilFrameChange -= deltaTime;

        if (_timeLeftUntilFrameChange <= 0.0f)
        {
            // it's time to switch to the next frame
            _currentFrame = (_currentFrame + 1) % _totalFrames; // looping
            this->setCurrentFrame();
            _timeLeftUntilFrameChange += Constants::FRAME_DURATION;
        }
    }

    // getters
    int getCurrentFrame() const { return this->_currentFrame; }
    // setters
    void setCurrentFrame(int currentFrame) { this->_currentFrame = currentFrame; }
    void setCurrentFrame() { this->_box.x = this->_box.w * this->_currentFrame; }
};

class AnimatedSpriteContainer {
protected:
    AnimatedSprite _animatedSprite;
public:
    AnimatedSpriteContainer(): _animatedSprite(AnimatedSprite()) {};
    AnimatedSpriteContainer(const AnimatedSprite& animatedSprite): _animatedSprite(animatedSprite) {};
    ~AnimatedSpriteContainer() {};
    const AnimatedSprite& getAnimatedSprite() const { return this->_animatedSprite; };
};
