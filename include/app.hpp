#pragma once
#include <memory>
#include "renderwindow.hpp"
#include "inputmanager.hpp"
#include "player.hpp"
#include "collisionmanager.hpp"

class App
{
public:
    App(RenderWindow& window):
    _window(window), 
    _inputManager(std::make_unique<InputManager>()),
    _collisionManager(std::make_unique<CollisionManager>()) {};

    void run() const;
    void handleInputs(Player& player1, Player& player2) const;
private:
    RenderWindow& _window;
    std::unique_ptr<InputManager> _inputManager;
    std::unique_ptr<CollisionManager> _collisionManager;
};
