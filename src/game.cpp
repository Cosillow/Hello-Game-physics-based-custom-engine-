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
	if (this->_inputManager->isKeyDown(SDL_SCANCODE_LEFT)) 
	{
		player1.moveLeft(true);
	}
	if (this->_inputManager->isKeyUp(SDL_SCANCODE_LEFT))
	{
		player1.moveLeft(false);
	}
	if (this->_inputManager->isKeyDown(SDL_SCANCODE_RIGHT)) 
	{
		player1.moveRight(true);
	}
	if (this->_inputManager->isKeyUp(SDL_SCANCODE_RIGHT))
	{
		player1.moveRight(false);
	}
	if (this->_inputManager->isKeyDown(SDL_SCANCODE_Z))
	{
		player1.jump();
	}
	if (this->_inputManager->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		this->_debugMenu = !this->_debugMenu;
	}
	if (this->_inputManager->isMouseButtonDown(SDL_BUTTON_LEFT))
	{
		this->_platforms.push_back(std::make_unique<Platform>(this->_camera->screenToWorld(this->_inputManager->getMousePosition()), 3));
	}
	if (this->_inputManager->isMouseButtonDown(SDL_BUTTON_RIGHT))
	{
		this->_platforms.clear();
	}
	
}

void Game::render() 
{
	if (this->_debugMenu) this->_userInterface->displayDebugMenu(this->_window, *this->_player);
	
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
	
	Uint32 currentTime = SDL_GetTicks();
	float accumulator = 0;
	const double dt = 0.01;

    int frames = 0;
    Uint32 fpsTimer = currentTime;

	Rope r = Rope(100, this->_player->getPosition());
	while (this->_gameRunning)
	{
		Uint32 newTime = SDL_GetTicks();
        float frameTime = (newTime - currentTime) / 1000.0f; // convert to seconds
		currentTime = newTime;
		accumulator += frameTime;
		++frames;
        
		this->handleInputs(*this->_player);

		while (accumulator >= dt)
		{
			// update
			this->_camera->update(dt);

			this->_player->update(dt);
			r.setPosition(this->_camera->screenToWorld(this->_inputManager->getMousePosition()));
			r.update(dt);

			// resolve collisions
			auto& segs = r.getSegments();
			for (auto& seg : segs)
			{
				this->_collisionManager->resolveBounds(const_cast<Body&>(*seg));
			}
			this->_collisionManager->resolveBounds(*this->_player);
			for (auto& p : this->_platforms)
			{
				this->_collisionManager->resolveBounds(*this->_player, *p);
			}

			accumulator -= dt;
		}
		
		// clear
		this->_window.clear();
		this->_userInterface->newFrame();

		this->_window.render(r);
		this->render();
		
		// display
		this->_window.display();

		// Calculate and print FPS every second
        Uint32 elapsed = SDL_GetTicks() - fpsTimer;
        if (elapsed >= 1000)
        {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            fpsTimer = SDL_GetTicks();
        }
	}
}
