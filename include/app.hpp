#pragma once

#include <memory>

#include "renderwindow.hpp"
#include "inputmanager.hpp"
#include "player.hpp"


class App
{
public:
    App(RenderWindow& window): _window(window), _inputManager(std::make_shared<InputManager>()) {};
    void run() const;
    void handleInputs(Player& player1, Player& player2) const;
private:
    RenderWindow& _window;
    std::shared_ptr<InputManager> _inputManager;
};