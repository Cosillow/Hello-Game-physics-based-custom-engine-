#include "camera.hpp"

Vector2 Camera::worldToScreen(const Vector2& world)
{
    return world - ( this->_center - (this->_size / 2.0f) );
}

void Camera::watchPlayer(const std::shared_ptr<Player>& player)
{
    _player = player;
}

void Camera::update(float deltaTime)
{
    if (this->_player == nullptr)
        return;
    this->_center = this->_player->getPosition();
}