#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


#include "player.hpp"
#include "inputmanager.hpp"
#include "constants.hpp"

//makes the player go upwards
void Player::moveUp(bool start) {
    if(start) {
       Entity::getPos().y = Entity::getPos().y - Constants::PLAYER_SPEED;
       std::cout << "move up" << std::endl;
    }
}
//changes the direction to be going downwards
void Player::moveDown(bool start) {
    if(start) {
        Entity::getPos().y = Entity::getPos().y + Constants::PLAYER_SPEED;
        std::cout << "move down" << std::endl;
    }
}
//makes the player go upwards
void Player::moveRight(bool start) {
    if (start) {
        Entity::getPos().x = Entity::getPos().x + Constants::PLAYER_SPEED;
        std::cout << "move right" << std::endl;
    }
}
//changes the direction to be going downwards
void Player::moveLeft(bool start) {
    if(start) {
        Entity::getPos().x = Entity::getPos().x - Constants::PLAYER_SPEED;
        std::cout << "move left" << std::endl;
    }
}