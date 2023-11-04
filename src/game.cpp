#include <iostream>
#include <vector>
#include <string>
#include <iostream>

#include "game.hpp"
#include "2dphysics.hpp"
#include "player.hpp"
#include "resourcemanager.hpp"
#include "sprite.hpp"
#include "platform.hpp"

void Game::handleInputs(Player& player1) {
	this->_inputManager->update(*this);

	// player 1
	if (this->_inputManager->isKeyDown(SDL_SCANCODE_A)) 
	{
		player1.moveLeft(true);
	}
	if (this->_inputManager->isKeyUp(SDL_SCANCODE_A))
	{
		player1.moveLeft(false);
	}
	if (this->_inputManager->isKeyDown(SDL_SCANCODE_D)) 
	{
		player1.moveRight(true);
	}
	if (this->_inputManager->isKeyUp(SDL_SCANCODE_D))
	{
		player1.moveRight(false);
	}
	if (this->_inputManager->isKeyDown(SDL_SCANCODE_SPACE))
	{
		player1.jump();
	}
	if (this->_inputManager->isMouseButtonDown(SDL_BUTTON_LEFT))
	{
		this->_platforms.push_back(std::make_unique<Platform>(this->_inputManager->getMousePosition(), 1));
	}
	if (this->_inputManager->isMouseButtonUp(SDL_BUTTON_LEFT))
	{

	}
}

void Game::run() {

	Player wilson({400, 200});
	
	// Canvas spriteTool;

	Uint32 prevTime = SDL_GetTicks();
	float deltaTime = 0;
	while (this->_gameRunning)
	{
		Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f; // Convert to seconds
        prevTime = currentTime;
        
		this->handleInputs(wilson);

		// clear
		this->_window.clear();
		this->_userInterface->newFrame();
		
		// update
		wilson.update(deltaTime);

		// resolve collisions
		this->_collisionManager->resolveBounds(wilson);

		for (auto& p : this->_platforms)
		{
			this->_collisionManager->resolveBounds(wilson, *p);
		}

		// render
		this->_userInterface->displayDebugMenu(this->_window, wilson);
		this->_window.render(wilson);
		for (auto& p : this->_platforms)
		{
			this->_window.render(*p);
		}

		this->_userInterface->renderFrame();
		
		// display
		this->_window.display();
	}
}
