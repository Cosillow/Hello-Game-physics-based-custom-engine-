#pragma once
#include <memory>
#include "renderwindow.hpp"
#include "inputmanager.hpp"
#include "player.hpp"
#include "collisionmanager.hpp"

class Canvas;

class Game
{
public:
    Game(RenderWindow& window):
    _gameRunning(true),
    _window(window), 
    _inputManager(std::make_unique<InputManager>()),
    _collisionManager(std::make_unique<CollisionManager>()) {};

    void run();
    void handleInputs(Player& player1, Canvas& canvas);
    void quit() { _gameRunning = false; }
private:
    bool _gameRunning;
    RenderWindow& _window;
    std::unique_ptr<InputManager> _inputManager;
    std::unique_ptr<CollisionManager> _collisionManager;
};
