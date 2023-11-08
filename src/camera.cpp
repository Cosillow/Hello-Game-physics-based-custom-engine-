#include "camera.hpp"

Vector2 Camera::worldToScreen(const Vector2& worldPosition)
{
    return (worldPosition - this->_center) + Vector2(Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f);
}

SDL_Rect Camera::worldToScreen(const SDL_Rect& worldRect)
{
    SDL_Rect screenRect;
    screenRect.x = static_cast<int>((worldRect.x - this->_center.x) + Constants::WINDOW_WIDTH / 2.0f);
    screenRect.y = static_cast<int>((worldRect.y - this->_center.y) + Constants::WINDOW_HEIGHT / 2.0f);
    screenRect.w = static_cast<int>(worldRect.w);
    screenRect.h = static_cast<int>(worldRect.h);

    return screenRect;
}

Vector2 Camera::screenToWorld(const Vector2& screenPosition)
{
    return (screenPosition + this->_center) - Vector2(Constants::WINDOW_WIDTH / 2.0f, Constants::WINDOW_HEIGHT / 2.0f);
}

void Camera::watchPlayer(const std::shared_ptr<Player>& player)
{
    this->_player = player;
}

void Camera::update(float deltaTime)
{
    if (this->_player == nullptr)
        return;
    auto p = this->_player->getPosition();
    const float scaleFactor = 3.0f;
    this->_center.x += scaleFactor*((p.x - this->_center.x) * deltaTime);
    this->_center.y = p.y;
}
