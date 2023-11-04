#pragma once
#include <memory>
#include "renderwindow.hpp"
#include "inputmanager.hpp"
#include "player.hpp"
#include "collisionmanager.hpp"
#include "userinterface.hpp"
#include "platform.hpp"

class Game
{
public:
    Game(RenderWindow& window):
    _gameRunning(true)
    , _window(window)
    , _inputManager(std::make_unique<InputManager>())
    , _collisionManager(std::make_unique<CollisionManager>())
    , _userInterface(std::make_unique<UserInterface>())
    , _platforms(std::vector<std::unique_ptr<Platform>>())
    {};

    void run();
    void handleInputs(Player& player1);
    void quit() { _gameRunning = false; }
private:
    bool _gameRunning;
    RenderWindow& _window;
    std::unique_ptr<InputManager> _inputManager;
    std::unique_ptr<CollisionManager> _collisionManager;
    std::unique_ptr<UserInterface> _userInterface;
    std::vector<std::unique_ptr<Platform>> _platforms;
};
