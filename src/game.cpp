#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <memory>

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
	if (this->_inputManager->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		this->_debugMenu = !this->_debugMenu;
	}
	if (this->_inputManager->isMouseButtonDown(SDL_BUTTON_LEFT))
	{
		this->_platforms.push_back(std::make_unique<Platform>(this->_camera->screenToWorld(this->_inputManager->getMousePosition()), 1));
	}
	if (this->_inputManager->isMouseButtonDown(SDL_BUTTON_RIGHT))
	{
		this->_platforms.clear();
	}
	
}

void Game::render() 
{
	if (this->_debugMenu)
		this->_userInterface->displayDebugMenu(this->_window, *this->_player);
	
	this->_window.render( *this->_player);
	for (auto& p : this->_platforms)
	{
		this->_window.render(*p);
	}

	this->_window.render();
	this->_userInterface->renderFrame();
}

void Game::run()
{
	this->_player = std::make_shared<Player>();
	this->_window.addCamera(this->_camera);
	this->_camera->watchPlayer(this->_player);
	
	Uint32 prevTime = SDL_GetTicks();
	float deltaTime = 0;
	while (this->_gameRunning)
	{
		Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f; // Convert to seconds
        prevTime = currentTime;
        
		this->handleInputs(*this->_player);

		// clear
		this->_window.clear();
		this->_userInterface->newFrame();
		
		// update
		this->_player->update(deltaTime);
		this->_camera->update(deltaTime);

		// resolve collisions
		this->_collisionManager->resolveBounds(*this->_player);
		for (auto& p : this->_platforms)
		{
			this->_collisionManager->resolveBounds(*this->_player, *p);
		}

		this->render();
		
		// display
		this->_window.display();
	}
}
