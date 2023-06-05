#include <iostream>
#include <vector>
#include <string>
#include <iostream>

#include "game.hpp"
#include "2dphysics.hpp"
#include "player.hpp"
#include "sword.hpp"
#include "grapplinghook.hpp"
#include "rope.hpp"
#include "resourcemanager.hpp"
#include "sprite.hpp"

void Game::handleInputs(Player& player1) {
	_inputManager->update(*this);
	
	// player 1
	// player1.setLookAngle(_inputManager->getMousePosition());
	if (_inputManager->isKeyDown(SDL_SCANCODE_A)) 
	{
		player1.moveLeft(true);
	}

	if (_inputManager->isKeyUp(SDL_SCANCODE_A))
	{
		player1.moveLeft(false);
	}

	if (_inputManager->isKeyDown(SDL_SCANCODE_D)) 
	{
		player1.moveRight(true);
	}

	if (_inputManager->isKeyUp(SDL_SCANCODE_D))
	{
		player1.moveRight(false);
	}

	if (_inputManager->isKeyDown(SDL_SCANCODE_SPACE))
	{
		player1.jump();
	}

    if (_inputManager->isMouseButtonDown(SDL_BUTTON_LEFT))
    {
		// rope.setStartLink(_inputManager->getMousePosition());
    }

}

void Game::run() {
    // Texture spaceDoritoTex(_window.getRenderer(), "res/spaceDorito.png");
	// Texture swordTex(_window.getRenderer(), "res/sword.png");
	
	Player wilson({400, 200});
	// Player spilson({200, 55});

	// spilson.setPosition({500,500});

	Sword doriSword({100, -200}, wilson);
	
	
	// ResourceManager resourceManager(this->_window.getRenderer(), std::vector<std::string>{"./res/monkey.png"});
	// Sword spillySword({-100, -200}, spilson);

	// GrapplingHook hook(wilson);

	// spilson.equipItem(&spillySword);
	// wilson.equipItem(&hook);

	// Rope rope({500, 200}, 20);
	// rope.setStartLink(&wilson);
	


	Uint32 prevTime = SDL_GetTicks();
	float deltaTime = 0;


	while (this->_gameRunning)
	{
		Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - prevTime) / 1000.0f; // Convert to seconds
        prevTime = currentTime;
        
		handleInputs(wilson);

		// clear
		_window.clear();

		// update
		wilson.update(deltaTime);		
		_collisionManager->resolveBounds(wilson);
		
		std::cout << wilson << std::endl;
		// render
		_window.render(wilson);
		
		// display
		_window.display();
	}
}
